#include "AGFTGameMode.h"

#include "AGFourTale/DamageSystem/AGFTHealthSystem.h"
#include "AGFourTale/Interfaces/AGFTPawnInterface.h"


void AAGFTGameMode::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	if (Players.Num() < 4) //Only support 4 players. Other players will be specators
	{
		Players.Add(NewPlayer);
	
		Super::HandleStartingNewPlayer_Implementation(NewPlayer);
	}
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

void AAGFTGameMode::PlayerDied(AActor* DeadActor, APlayerState* DamageInstigator)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, DeadActor->GetName());
}
