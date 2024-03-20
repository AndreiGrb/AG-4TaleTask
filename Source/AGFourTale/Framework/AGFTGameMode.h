#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AGFTGameMode.generated.h"

UCLASS(minimalapi)
class AAGFTGameMode : public AGameModeBase
{
	GENERATED_BODY()

private:
	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;

	TArray<TWeakObjectPtr<APlayerController>> Players;

	virtual void BeginPlay() override;
	
	virtual APawn* SpawnDefaultPawnAtTransform_Implementation(AController* NewPlayer, const FTransform& SpawnTransform) override;

	
	UFUNCTION()
	void PlayerDied(AActor* DeadActor, APlayerState* DamageInstigator);
};
