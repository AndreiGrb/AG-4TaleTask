#include "AGFTGameState.h"

#include "AGFTPlayerController.h"
#include "Net/UnrealNetwork.h"


void AAGFTGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(AAGFTGameState, bMatchStarted);
	DOREPLIFETIME(AAGFTGameState, bMatchIsOver);
	DOREPLIFETIME(AAGFTGameState, RespawnDuration);
}

void AAGFTGameState::OnRep_MatchStarted()
{
	//Do if check. PlayerController could be nullptr
	if (const auto PlayerController = Cast<AAGFTPlayerController>(GetWorld()->GetFirstPlayerController()))
	{	
		PlayerController->Server_RequestMatchTime();
	}
}

void AAGFTGameState::OnRep_MatchIsOver()
{
	if (AAGFTPlayerController* PlayerController = Cast<AAGFTPlayerController>(GetWorld()->GetFirstPlayerController()))
	{
		PlayerController->MatchIsOver();
	}
}
