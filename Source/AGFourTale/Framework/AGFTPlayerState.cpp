#include "AGFTPlayerState.h"

#include "Net/UnrealNetwork.h"

void AAGFTPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AAGFTPlayerState, NumberOfKills);
	DOREPLIFETIME(AAGFTPlayerState, NumberOfDeaths);
}
