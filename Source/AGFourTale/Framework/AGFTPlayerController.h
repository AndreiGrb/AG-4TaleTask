#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AGFTPlayerController.generated.h"


UCLASS()
class AGFOURTALE_API AAGFTPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(Server, Reliable)
	void Server_DamageOtherActor(AActor* OtherActor, int32 Damage);

private:
	virtual void EndPlayingState() override;
};
