#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AGFTPlayerState.generated.h"


UCLASS()
class AGFOURTALE_API AAGFTPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	UPROPERTY(Replicated)
	int32 NumberOfKills;

	UPROPERTY(Replicated)
	int32 NumberOfDeaths;
	
private:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
