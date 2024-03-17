#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AGFTPawnInterface.generated.h"


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
};
