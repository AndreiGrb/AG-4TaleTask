#include "AGFTGameMode.h"

#include "AGFTGameState.h"
#include "AGFTPlayerState.h"
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
	NewPlayerIndex++;
	
	if (GetNumPlayers() > 1)
	{
		StartMatch();
	}
	if (GetNumPlayers() <= 4) //Only support 4 players. Other players will be spectators
	{
		const auto PlayerState = NewPlayer->GetPlayerState<AAGFTPlayerState>();
		
		PlayerState->SetPlayerName(FString::Printf(TEXT("Player %i"), NewPlayerIndex));
		PlayerState->SetPlayerId(NewPlayerIndex);
		
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
	AGFTGameState->KillsToWin = KillsToWin;

	if (IsNetMode(NM_ListenServer))
	{
		AGFTGameState->OnRep_MatchStarted();
	}
}

void AAGFTGameMode::HandleMatchProgress(float DeltaSeconds)
{
	if (!bIsMatchStarted)
	{
		return;
	}

	int32 PlayerID;
	const int32 CurrentHighestAmountOfKills = GetHighestAmountOfKill(PlayerID);
	
	DurationOfMatch -= DeltaSeconds;

	if ((DurationOfMatch < 0.f || CurrentHighestAmountOfKills >= KillsToWin) && !bMatchIsOver)
	{
		bMatchIsOver = true;
		
		GetWorldTimerManager().SetTimer(MatchIsOverTimerHandle, this,
										&AAGFTGameMode::RestartLevel,
										WaitTimeAfterMatchIsOver);

		const int32 WinnerID = DetermineWinner();
		
		const auto AGFTGameState = Cast<AAGFTGameState>(GameState);
		AGFTGameState->bMatchIsOver = true;
		AGFTGameState->WinnerID = WinnerID;

		if (IsNetMode(NM_ListenServer))
		{
			AGFTGameState->OnRep_MatchIsOver();
		}
	}
}

void AAGFTGameMode::PlayerDied(AActor* DeadActor, APlayerState* DamageInstigator)
{
	AAGFTPlayerState* PlayerState = Cast<APawn>(DeadActor)->GetPlayerState<AAGFTPlayerState>();
	PlayersWaitingForRespawn.Add(PlayerState, RespawnTimer);

	if (bIsMatchStarted && !bMatchIsOver)
	{
		PlayerState->NumberOfDeaths++;
		Cast<AAGFTPlayerState>(DamageInstigator)->NumberOfKills++;
	}
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

void AAGFTGameMode::RestartLevel()
{
	GetWorld()->ServerTravel("?Restart",false);
}

int32 AAGFTGameMode::GetHighestAmountOfKill(int32& PlayerID) const
{
	const auto AGFTGameState = Cast<AAGFTGameState>(GameState);

	int32 HighestKillCount = -1;
	for (TObjectPtr<APlayerState> PlayerState : AGFTGameState->PlayerArray)
	{
		const auto AGFTPlayerState = Cast<AAGFTPlayerState>(PlayerState);

		if (AGFTPlayerState->NumberOfKills > HighestKillCount)
		{
			HighestKillCount = AGFTPlayerState->NumberOfKills;
			PlayerID = AGFTPlayerState->GetPlayerId();
		}
	}
	
	return HighestKillCount;
}

int32 AAGFTGameMode::DetermineWinner() const
{
	int32 WinnerID;
	GetHighestAmountOfKill(WinnerID);
	
	return WinnerID;
}
