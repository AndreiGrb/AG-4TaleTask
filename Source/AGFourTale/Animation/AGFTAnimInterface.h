#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AGFTAnimInterface.generated.h"


UINTERFACE()
class UAGFTAnimInterface : public UInterface
{
	GENERATED_BODY()
};


class AGFOURTALE_API IAGFTAnimInterface
{
	GENERATED_BODY()

public:
	virtual void PlaySwitchWeaponAnimation();
	virtual void WeaponSwitched();
};
