#include "AGFTWeapon.h"

#include "AGFTProjectile.h"
#include "AGFourTale/Utils/AGFTLogCategories.h"
#include "AGFourTale/Utils/AGFTNames.h"


void AAGFTWeapon::ShootPressed()
{
	if (!ProjectileClass)
	{
		UE_LOG(LogWeapon, Error, TEXT("[AAGFTWeapon::ShootPressed] ProjectileClass == nullptr"));
		return;
	}
	
	const FVector ShootLocation = GetRootComponent()->GetSocketLocation(SOCKETNAME_WEAPON_SHOOT);
	const FRotator ShootRotation = GetActorRightVector().ToOrientationRotator();

	GetWorld()->SpawnActor<AAGFTProjectile>(ProjectileClass, ShootLocation, ShootRotation);
}

void AAGFTWeapon::ShootReleased()
{
}

AAGFTWeapon::AAGFTWeapon()
{
	WeaponMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMeshComponent);
}
