#pragma once

#include "CoreMinimal.h"
#include "AGFourTale/Design/AGFTWeaponsConfig.h"
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
	
	void ShootProjectile();

	
	FOnWeaponFired OnWeaponFired;

private:
	AAGFTWeapon();

	virtual void BeginPlay() override;
	
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> WeaponMeshComponent;
	

	void FindWeaponConfigFromDT();

	FAGFTWeaponConfig WeaponConfig;
	
	UPROPERTY(EditAnywhere, Category = "Settings")
	FDataTableRowHandle WeaponConfigDTRowHandle;


	FTimerHandle CooldownBetweenShotsTimerHandle;

	UFUNCTION()
	void CooldownBetweenShotsExpired();
	
	bool bIsInCooldown;

	bool bIsShootPressed;
};