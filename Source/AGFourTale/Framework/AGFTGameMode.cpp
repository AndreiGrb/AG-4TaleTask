#include "AGFTGameMode.h"

#include "AGFTGameState.h"
#include "AGFourTale/DamageSystem/AGFTHealthSystem.h"
#include "AGFourTale/Interfaces/AGFTPawnInterface.h"
#include "GameFramework/PlayerState.h"


AAGFTGameMode::AAGFTGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAGFTGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	HandleRespawnTimers(DeltaSeconds);

	HandleMatchProgress(DeltaSeconds);
}

void AAGFTGameMode::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	if (GetNumPlayers() > 1)
	{
		StartMatch();
	}
	if (GetNumPlayers() < 4) //Only support 4 players. Other players will be spectators
	{
		Super::HandleStartingNewPlayer_Implementation(NewPlayer);
	}
}

APawn* AAGFTGameMode::SpawnDefaultPawnAtTransform_Implementation(AController* NewPlayer,
																 const FTransform& SpawnTransform)
{
	APawn* SpawnedPawn = Super::SpawnDefaultPawnAtTransform_Implementation(NewPlayer, SpawnTransform);
	if (const auto PawnInterface = Cast<IAGFTPawnInterface>(SpawnedPawn))
	{
		if (PawnInterface->GetHealthComponent())
		{
			PawnInterface->GetHealthComponent()->OnDeath.AddDynamic(this, &AAGFTGameMode::PlayerDied);
		}
	}
	return SpawnedPawn;
}

void AAGFTGameMode::StartMatch()
{
	bIsMatchStarted = true;

	const auto AGFTGameState = Cast<AAGFTGameState>(GameState);
	AGFTGameState->bMatchStarted = true;
	AGFTGameState->RespawnDuration = RespawnTimer;
}

void AAGFTGameMode::HandleMatchProgress(float DeltaSeconds)
{
	if (!bIsMatchStarted)
	{
		return;
	}
		
	DurationOfMatch -= DeltaSeconds;

	if (DurationOfMatch < 0.f)
	{
		DurationOfMatch = 10000.f;
		GetWorldTimerManager().SetTimer(MatchIsOverTimerHandle, this,
										&AAGFTGameMode::MatchIsOver,
										WaitTimeAfterMatchIsOver);

		GetGameState<AAGFTGameState>()->bMatchIsOver = true;
	}
}

void AAGFTGameMode::PlayerDied(AActor* DeadActor, APlayerState* DamageInstigator)
{
	APlayerState* PlayerState = Cast<APawn>(DeadActor)->GetPlayerState();
	PlayersWaitingForRespawn.Add(PlayerState, RespawnTimer);
}

void AAGFTGameMode::HandleRespawnTimers(const float DeltaSeconds)
{
	for (auto It = PlayersWaitingForRespawn.CreateIterator(); It; ++It)
	{
		if (!IsValid(It->Key.Get()))
		{	//If dead player is no longer exist
			It.RemoveCurrent();
			continue;
		}
		
		It->Value -= DeltaSeconds;

		if (It->Value < 0.f)
		{
			RespawnPlayer(It->Key.Get());
			It.RemoveCurrent();
		}
	}
}

void AAGFTGameMode::RespawnPlayer(const APlayerState* DeadPlayer)
{
	if (!IsValid(DeadPlayer))
	{
		return;
	}

	const auto PlayerStart = ChoosePlayerStart(DeadPlayer->GetPlayerController());
	
	if (const auto PawnInterface = Cast<IAGFTPawnInterface>(DeadPlayer->GetPawn()))
	{
		PawnInterface->RevivePawn(PlayerStart->GetActorRotation());
	}
	
	DeadPlayer->GetPawn()->SetActorLocation(PlayerStart->GetActorLocation());
}

void AAGFTGameMode::MatchIsOver()
{
	GetWorld()->ServerTravel("?Restart",false);
}
