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
	
	virtual void Tick(float DeltaSeconds) override;
	
	
	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;

	virtual APawn* SpawnDefaultPawnAtTransform_Implementation(AController* NewPlayer, const FTransform& SpawnTransform) override;
	

	bool bIsMatchStarted;

	UPROPERTY(EditAnywhere, Category = "Settings")
	float DurationOfMatch = 300.f /*5 min*/;

	void HandleMatchProgress(float DeltaSeconds);

	
	UFUNCTION()
	void PlayerDied(AActor* DeadActor, APlayerState* DamageInstigator);
	
	UPROPERTY(EditAnywhere, Category = "Settings")
	float RespawnTimer = 5.f;

	TMap<TWeakObjectPtr<APlayerState>, float> PlayersWaitingForRespawn;

	void HandleRespawnTimers(const float DeltaSeconds);

	void RespawnPlayer(const APlayerState* DeadPlayer);


	void MatchIsOver();
};
