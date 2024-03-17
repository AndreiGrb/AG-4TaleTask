#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AGFTProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class AGFOURTALE_API AAGFTProjectile : public AActor
{
	GENERATED_BODY()

private:
	AAGFTProjectile();
	
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> SphereCollisionComponent;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> ProjectileBodyComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;
};
