#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AGFTWeapon.generated.h"

class AAGFTProjectile;

UCLASS()
class AGFOURTALE_API AAGFTWeapon : public AActor
{
	GENERATED_BODY()

public:
	void ShootPressed();
	void ShootReleased();

private:
	AAGFTWeapon();
	
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> WeaponMeshComponent;

	UPROPERTY(EditAnywhere, Category = "Settings")
	TSubclassOf<AAGFTProjectile> ProjectileClass;
};
