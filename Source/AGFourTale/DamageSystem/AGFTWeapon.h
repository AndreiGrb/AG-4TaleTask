#pragma once

#include "CoreMinimal.h"
#include "AGFourTale/Design/AGFTWeaponsConfig.h"
#include "GameFramework/Actor.h"
#include "AGFTWeapon.generated.h"

class AAGFTProjectile;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnWeaponFired_ForServer, TSubclassOf<AAGFTWeapon>, WeaponClass, const FVector&, ShootLocation, const FRotator&, ShootRotation);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponFired);

UCLASS()
class AGFOURTALE_API AAGFTWeapon : public AActor
{
	GENERATED_BODY()

public:
	void ShootPressed();
	void ShootReleased();
	
	void ShootProjectile(const FVector& ShootLocation, const FRotator& ShootRotation);
	
	FOnWeaponFired_ForServer OnWeaponFired_ForServer;
	FOnWeaponFired OnWeaponFired;


	void GetAmmoCount(int32& CurrentMagAmmoCount, int32& CurrentWeaponAmmoCount);
	//Should only be called on weapon switch
	void SetAmmoCount(const int32 CurrentMagAmmoCount, const int32 CurrentWeaponAmmoCount);


	FORCEINLINE const FDataTableRowHandle& GetWeaponConfigRowHandle() const { return WeaponConfigDTRowHandle; }
	FORCEINLINE const FAGFTWeaponConfig& GetWeaponConfig() const { return WeaponConfig; }

private:
	AAGFTWeapon();

	virtual void BeginPlay() override;
	
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> WeaponMeshComponent;
	

	void FindWeaponConfigFromDT();

	FAGFTWeaponConfig WeaponConfig;
	
	UPROPERTY(EditAnywhere, Category = "Settings")
	FDataTableRowHandle WeaponConfigDTRowHandle;


	void InitAmmoCount();

	//todo: make a struct, if more variables are added beside ammo
	int32 MagAmmoCount;
	int32 WeaponAmmoCount;


	FTimerHandle CooldownBetweenShotsTimerHandle;

	UFUNCTION()
	void CooldownBetweenShotsExpired();
	
	bool bIsInCooldown;

	bool bIsShootPressed;


	float GetRandomSpread() const;
};