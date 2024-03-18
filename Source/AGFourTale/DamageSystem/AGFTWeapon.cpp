#include "AGFTWeapon.h"

#include "AGFTProjectile.h"
#include "AGFourTale/Design/AGFTWeaponsConfig.h"
#include "AGFourTale/Utils/AGFTLogCategories.h"
#include "AGFourTale/Utils/AGFTNames.h"


void AAGFTWeapon::ShootPressed()
{
	if (!WeaponConfig.ProjectileClass)
	{
		UE_LOG(LogWeapon, Error, TEXT("[AAGFTWeapon::ShootPressed] ProjectileClass == nullptr"));
		return;
	}

	if (bIsInCooldown)
	{
		return;
	}
	bIsInCooldown = true;
	bIsShootPressed = true;

	ShootProjectile();
	
	GetWorldTimerManager().SetTimer(CooldownBetweenShotsTimerHandle, this,
										&AAGFTWeapon::CooldownBetweenShotsExpired,
										WeaponConfig.FireRate);
}

void AAGFTWeapon::ShootReleased()
{
	bIsShootPressed = false;
}

void AAGFTWeapon::ShootProjectile()
{
	const FVector& ShootLocation = GetRootComponent()->GetSocketLocation(SOCKETNAME_WEAPON_SHOOT);
	const FRotator& ShootRotation = GetActorRightVector().ToOrientationRotator();
	
	if (IsNetMode(NM_Client))
	{
		OnWeaponFired.Broadcast(GetClass(), ShootLocation, ShootRotation);
	}
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = GetOwner();
	GetWorld()->SpawnActor<AAGFTProjectile>(WeaponConfig.ProjectileClass, ShootLocation, ShootRotation, SpawnParameters);
}

AAGFTWeapon::AAGFTWeapon()
{
	WeaponMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMeshComponent);
}

void AAGFTWeapon::BeginPlay()
{
	Super::BeginPlay();

	FindWeaponConfigFromDT();
}

void AAGFTWeapon::FindWeaponConfigFromDT()
{
	if (!WeaponConfigDTRowHandle.DataTable || WeaponConfigDTRowHandle.RowName.IsNone())
	{
		UE_LOG(LogWeapon, Error, TEXT("[AAGFTWeapon::FindWeaponConfigFromDT] WeaponConfigDTRowHandle is Null!"));
	}
	else
	{
		const auto RowData = WeaponConfigDTRowHandle.GetRow<FAGFTWeaponConfig>(TEXT(""));
		if (!RowData)
		{
			UE_LOG(LogWeapon, Error, TEXT("[AAGFTWeapon::FindWeaponConfigFromDT] Could not find any valid data."));
			return;
		}
		WeaponConfig = *RowData;
	}
}

void AAGFTWeapon::CooldownBetweenShotsExpired()
{
	bIsInCooldown = false;

	if (bIsShootPressed && WeaponConfig.bIsAutomatic)
	{
		ShootPressed();
	}
}
