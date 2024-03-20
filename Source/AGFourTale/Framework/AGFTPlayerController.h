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


	UFUNCTION(Server, Reliable)
	void Server_RequestMatchTime();

	UFUNCTION(Client, Reliable)
	void Client_CurrentMatchTime(const float CurrentTime);

private:
	AAGFTPlayerController();
	
	virtual void Tick(float DeltaSeconds) override;
	
	virtual void EndPlayingState() override;


	float MatchTimeRemaining;
};
