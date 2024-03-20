#include "AGFTGameMode.h"

#include "AGFourTale/DamageSystem/AGFTHealthSystem.h"
#include "AGFourTale/Interfaces/AGFTPawnInterface.h"
#include "GameFramework/PlayerState.h"


AAGFTGameMode::AAGFTGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAGFTGameMode::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	if (Players.Num() < 4) //Only support 4 players. Other players will be spectators
	{
		Players.Add(NewPlayer);
	
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

void AAGFTGameMode::Logout(AController* Exiting)
{
	Players.Remove(Cast<APlayerController>(Exiting));
	
	Super::Logout(Exiting);
}

void AAGFTGameMode::BeginPlay()
{
	Super::BeginPlay();

	
}

void AAGFTGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

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

void AAGFTGameMode::PlayerDied(AActor* DeadActor, APlayerState* DamageInstigator)
{
	APlayerState* PlayerState = Cast<APawn>(DeadActor)->GetPlayerState();
	PlayersWaitingForRespawn.Add(PlayerState, RespawnTimer);
}

void AAGFTGameMode::RespawnPlayer(const APlayerState* DeadPlayer)
{
	if (!IsValid(DeadPlayer))
	{
		return;
	}
	
	if (const auto PawnInterface = Cast<IAGFTPawnInterface>(DeadPlayer->GetPawn()))
	{
		PawnInterface->RevivePawn();
	}
	RestartPlayer(DeadPlayer->GetPlayerController());
}
