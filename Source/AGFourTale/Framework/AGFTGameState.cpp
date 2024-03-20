#include "AGFTGameState.h"

#include "AGFTPlayerController.h"
#include "Net/UnrealNetwork.h"


void AAGFTGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(AAGFTGameState, bMatchStarted);
	DOREPLIFETIME(AAGFTGameState, bMatchIsOver);
}

void AAGFTGameState::OnRep_MatchStarted()
{
	Cast<AAGFTPlayerController>(GetWorld()->GetFirstPlayerController())->Server_RequestMatchTime();
}

void AAGFTGameState::OnRep_MatchIsOver()
{
	
}
