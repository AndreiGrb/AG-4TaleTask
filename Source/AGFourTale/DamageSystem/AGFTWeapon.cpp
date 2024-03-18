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
	GetWorld()->SpawnActor<AAGFTProjectile>(ProjectileClass, ShootLocation, ShootRotation, SpawnParameters);
}

AAGFTWeapon::AAGFTWeapon()
{
	WeaponMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMeshComponent);
}
