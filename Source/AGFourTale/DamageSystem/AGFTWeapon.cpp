#include "AGFTWeapon.h"

AAGFTWeapon::AAGFTWeapon()
{
	WeaponMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMeshComponent);
}
