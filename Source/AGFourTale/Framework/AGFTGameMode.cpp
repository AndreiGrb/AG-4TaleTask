#include "AGFTGameMode.h"


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
