#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AGFTGameMode.generated.h"

UCLASS(minimalapi)
class AAGFTGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	FORCEINLINE float GetMatchTime() const { return DurationOfMatch; }

private:
	AAGFTGameMode();
	
	virtual void Tick(float DeltaSeconds) override;
	

	int32 NewPlayerIndex;
	
	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;

	virtual APawn* SpawnDefaultPawnAtTransform_Implementation(AController* NewPlayer, const FTransform& SpawnTransform) override;
	

	void StartMatch();
	
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


	UPROPERTY(EditAnywhere, Category = "Settings")
	float WaitTimeAfterMatchIsOver = 5.f;

	FTimerHandle MatchIsOverTimerHandle;

	bool bMatchIsOver;
	
	UFUNCTION()
	void RestartLevel();
	

	UPROPERTY(EditAnywhere, Category = "Settings")
	int32 KillsToWin = 10;

	int32 GetHighestAmountOfKill(int32& IdOfThatPlayer) const;
	
	int32 DetermineWinner() const;
};
