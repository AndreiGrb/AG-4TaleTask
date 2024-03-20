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

	bIsShootPressed = true;

	if (bIsInCooldown || MagAmmoCount < 1)
	{
		return;
	}
	bIsInCooldown = true;

	const FVector& ShootLocation = GetRootComponent()->GetSocketLocation(SOCKETNAME_WEAPON_SHOOT);
	const FRotator& ShootRotation = GetActorRightVector().ToOrientationRotator();
	ShootProjectile(ShootLocation, ShootRotation);
	
	GetWorldTimerManager().SetTimer(CooldownBetweenShotsTimerHandle, this,
										&AAGFTWeapon::CooldownBetweenShotsExpired,
										WeaponConfig.FireRate);

	MagAmmoCount--;
}

void AAGFTWeapon::ShootReleased()
{
	bIsShootPressed = false;
}

void AAGFTWeapon::ShootProjectile(const FVector& ShootLocation, const FRotator& ShootRotation)
{
	if (IsNetMode(NM_Client))
	{
		OnWeaponFired_ForServer.Broadcast(GetClass(), ShootLocation, ShootRotation);
	}
	OnWeaponFired.Broadcast();

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = GetOwner();
	
	for (int32 i = 0; i < WeaponConfig.NumberOfProjectilesPerShot; i++)
	{
		FRotator FinalShootRotation = ShootRotation;
		if (WeaponConfig.ProjectileRandomSpread > 0.f)
		{
			FRotator RotationDeviation = FRotator(GetRandomSpread(),
											GetRandomSpread(),
											GetRandomSpread());
			FinalShootRotation = ShootRotation + RotationDeviation;
		}

		GetWorld()->SpawnActor<AAGFTProjectile>(WeaponConfig.ProjectileClass, ShootLocation, FinalShootRotation, SpawnParameters);
	}
}

void AAGFTWeapon::GetAmmoCount(int32& CurrentMagAmmoCount, int32& CurrentWeaponAmmoCount)
{
	CurrentMagAmmoCount = MagAmmoCount;
	CurrentWeaponAmmoCount = WeaponAmmoCount;
}

void AAGFTWeapon::SetAmmoCount(const int32 NewMagAmmoCount, const int32 NewWeaponAmmoCount)
{
	MagAmmoCount = NewMagAmmoCount;
	WeaponAmmoCount = NewWeaponAmmoCount;
}

bool AAGFTWeapon::CanReload()
{
	return MagAmmoCount < WeaponConfig.MagAmmoCapacity && WeaponAmmoCount > 0;
}

void AAGFTWeapon::Reload()
{
	const int32 AmountNeeded = WeaponConfig.MagAmmoCapacity - MagAmmoCount;
	const int32 AvailableAmmo = FMath::Min(WeaponAmmoCount, AmountNeeded);
	
	MagAmmoCount += AvailableAmmo;
	WeaponAmmoCount -= AvailableAmmo;
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

	InitAmmoCount();
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

void AAGFTWeapon::InitAmmoCount()
{
	MagAmmoCount = WeaponConfig.MagAmmoCapacity;
	WeaponAmmoCount = MagAmmoCount * WeaponConfig.SpawnWithExtraMagazines;
}

void AAGFTWeapon::CooldownBetweenShotsExpired()
{
	bIsInCooldown = false;

	if (bIsShootPressed && WeaponConfig.bIsAutomatic)
	{
		ShootPressed();
	}
}

float AAGFTWeapon::GetRandomSpread() const
{
	return FMath::RandRange(-WeaponConfig.ProjectileRandomSpread,
							WeaponConfig.ProjectileRandomSpread);
}
