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
	
	const FVector ShootLocation = GetRootComponent()->GetSocketLocation(SOCKETNAME_WEAPON_SHOOT);
	const FRotator ShootRotation = GetActorRightVector().ToOrientationRotator();

	ShootProjectile(ShootLocation, ShootRotation);
}

void AAGFTWeapon::ShootReleased()
{
}

void AAGFTWeapon::ShootProjectile(const FVector& ShootLocation, const FRotator& ShootRotation)
{
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
		UE_LOG(LogWeapon, Error, TEXT("[AAGFTWeapon::BeginPlay] WeaponConfigDTRowHandle is Null!"));
	}
	else
	{
		const auto RowData = WeaponConfigDTRowHandle.GetRow<FAGFTWeaponConfig>(TEXT(""));
		if (!RowData)
		{
			UE_LOG(LogWeapon, Error, TEXT("[AAGFTWeapon::BeginPlay] Could not find any valid data."));
			return;
		}
		WeaponConfig = *RowData;
	}
}
