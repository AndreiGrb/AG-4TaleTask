#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AGFTPawnInterface.generated.h"


class AAGFTWeapon;

UINTERFACE()
class UAGFTPawnInterface : public UInterface
{
	GENERATED_BODY()
};


class AGFOURTALE_API IAGFTPawnInterface
{
	GENERATED_BODY()

public:
	//Optional, if pawn needs to replicate it's Yaw view, for animation purposes
	virtual float GetRemoteViewYaw() const;
	virtual void SetRemoteViewYaw(const float NewRemoteViewYaw);

	//Get current weapon, that pawn is holding, if it has one
	virtual AAGFTWeapon* GetCurrentHoldingWeapon() const;

	//Check if pawn is using aiming/ironsights
	virtual bool IsAiming() const;

	//Check if pawn is in orientation lock
	virtual bool IsOrientationLockActive() const;
};
