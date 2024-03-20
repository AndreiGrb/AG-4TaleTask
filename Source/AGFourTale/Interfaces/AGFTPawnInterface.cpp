#include "AGFTPawnInterface.h"


float IAGFTPawnInterface::GetRemoteViewYaw() const
{
	return 0.f;
}

void IAGFTPawnInterface::SetRemoteViewYaw(const float NewRemoteViewYaw)
{
	//Here should be overriden by Pawn to set RemoteViewYaw
}

AAGFTWeapon* IAGFTPawnInterface::GetCurrentHoldingWeapon() const
{
	return nullptr; //Here should be overriden by Pawn that using Weapons
}

bool IAGFTPawnInterface::IsAiming() const
{
	return false; //Override if pawn has aiming functionality
}

bool IAGFTPawnInterface::IsOrientationLockActive() const
{
	return false; //Override if pawn has orientation lock
}

bool IAGFTPawnInterface::CanShoot() const
{
	return false; //Override if pawn has capability to shoot
}

void IAGFTPawnInterface::SwitchWeapons()
{
	//Override if pawn needs switching weapons
}

void IAGFTPawnInterface::WeaponSwitchAnimComplete()
{
	//Override if pawn needs to receive this call from animation
}

void IAGFTPawnInterface::ReloadWeapon()
{
	//Override if pawn needs reloading weapon mechanic
}

void IAGFTPawnInterface::ReloadWeaponAnimComplete()
{
	//Override if pawn needs to receive this call from animation
}

int32 IAGFTPawnInterface::GetCurrentHealth() const
{
	return 0; //Override if pawn has a health value
}
