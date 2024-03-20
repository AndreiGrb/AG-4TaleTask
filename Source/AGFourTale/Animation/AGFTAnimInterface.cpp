#include "AGFTAnimInterface.h"


void IAGFTAnimInterface::PlaySwitchWeaponAnimation()
{
	//Override for switch weapon animation
}

void IAGFTAnimInterface::WeaponSwitched()
{
	//Override for when animation notified, that weapon has been switched
}

void IAGFTAnimInterface::PlayReloadAnimation()
{
	//Override for weapon reload animation
}

void IAGFTAnimInterface::WeaponReloaded()
{
	//Override for when animation notified, that weapon is reloaded
}

void IAGFTAnimInterface::Revived()
{
	//Override if anim variables needs to be reset after revive
}
