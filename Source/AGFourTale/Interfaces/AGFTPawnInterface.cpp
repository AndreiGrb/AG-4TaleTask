#include "AGFTPawnInterface.h"


float IAGFTPawnInterface::GetRemoteViewYaw() const
{
	return 0.f;
}

void IAGFTPawnInterface::SetRemoteViewYaw(const float NewRemoteViewYaw)
{
	//Here should be overriden by Pawn to set RemoteViewYaw
}

AAGFTWeapon* IAGFTPawnInterface::GetCurrentHoldingWeapon()
{
	return nullptr; //Here should be overriden by Pawn that using Weapons
}

bool IAGFTPawnInterface::IsAiming()
{
	return false; //Override if pawn has aiming functionality
}
