#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AGFTPickup.generated.h"

class USphereComponent;

UCLASS()
class AGFOURTALE_API AAGFTPickup : public AActor
{
	GENERATED_BODY()

private:
	AAGFTPickup();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;


	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> DefaultSceneComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UChildActorComponent> PickupActorComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> SphereCollision;
};
