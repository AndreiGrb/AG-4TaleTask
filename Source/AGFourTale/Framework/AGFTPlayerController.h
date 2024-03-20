#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AGFTPlayerController.generated.h"


class UInputMappingContext;
class UInputAction;

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

	void MatchIsOver();

private:
	AAGFTPlayerController();

	void BeginPlay();
	
	virtual void Tick(float DeltaSeconds) override;
	
	virtual void EndPlayingState() override;


	virtual void SetupInputComponent() override;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> LeaderboardAction;
	
	void OpenLeaderboard();
	void CloseLeaderboard();

	float MatchTimeRemaining;
};
