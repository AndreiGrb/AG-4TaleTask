#pragma once

#include "CoreMinimal.h"
#include "AGFourTale/Design/AGFTProjectilesConfig.h"
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

	virtual void BeginPlay() override;
	

	UFUNCTION()
	void OnProjectileHit( UPrimitiveComponent* HitComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> SphereCollisionComponent;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> ProjectileBodyComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;


	void FindProjectileConfigFromDT();

	FAGFTProjectileConfig ProjectileConfig;
	
	UPROPERTY(EditAnywhere, Category = "Settings")
	FDataTableRowHandle ProjectileConfigDTRowHandle;
};