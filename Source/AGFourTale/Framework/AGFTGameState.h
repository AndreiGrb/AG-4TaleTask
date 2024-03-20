#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "AGFTGameState.generated.h"


UCLASS()
class AGFOURTALE_API AAGFTGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	UPROPERTY(ReplicatedUsing = OnRep_MatchStarted)
	bool bMatchStarted;

	UPROPERTY(ReplicatedUsing = OnRep_MatchIsOver)
	bool bMatchIsOver;

	UPROPERTY(Replicated)
	float RespawnDuration;

private:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void OnRep_MatchStarted();

	UFUNCTION()
	void OnRep_MatchIsOver();
};
