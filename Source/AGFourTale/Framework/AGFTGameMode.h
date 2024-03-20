#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AGFTGameMode.generated.h"

UCLASS(minimalapi)
class AAGFTGameMode : public AGameModeBase
{
	GENERATED_BODY()

private:
	AAGFTGameMode();
	
	
	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;

	virtual APawn* SpawnDefaultPawnAtTransform_Implementation(AController* NewPlayer, const FTransform& SpawnTransform) override;
	
	virtual void Logout(AController* Exiting) override;

	TArray<TWeakObjectPtr<APlayerController>> Players;
	

	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaSeconds) override;

	
	UFUNCTION()
	void PlayerDied(AActor* DeadActor, APlayerState* DamageInstigator);
	
	UPROPERTY(EditAnywhere)
	float RespawnTimer = 5.f;

	TMap<TWeakObjectPtr<APlayerState>, float> PlayersWaitingForRespawn;

	void RespawnPlayer(const APlayerState* DeadPlayer);
};
