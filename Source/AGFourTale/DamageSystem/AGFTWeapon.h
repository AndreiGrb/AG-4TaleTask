#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AGFTWeapon.generated.h"

class AAGFTProjectile;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnWeaponFired, TSubclassOf<AAGFTWeapon>, WeaponClass, const FVector&, ShootLocation, const FRotator&, ShootRotation);

UCLASS()
class AGFOURTALE_API AAGFTWeapon : public AActor
{
	GENERATED_BODY()

public:
	void ShootPressed();
	void ShootReleased();

	void ShootProjectile(const FVector& ShootLocation, const FRotator& ShootRotation);

	
	FOnWeaponFired OnWeaponFired;

private:
	AAGFTWeapon();
	
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> WeaponMeshComponent;

	UPROPERTY(EditAnywhere, Category = "Settings")
	TSubclassOf<AAGFTProjectile> ProjectileClass;
};