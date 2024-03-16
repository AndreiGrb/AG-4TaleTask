#include "AGFTFunctionLibrary.h"

#include "Kismet/KismetSystemLibrary.h"

float FAGFTUtils::GetReplicatedPitchValue(const APawn* FromPawn)
{
	if (!IsValid(FromPawn))
	{
		return 0.f;
	}
	if (FromPawn->GetController() && FromPawn->IsLocallyControlled())
	{
		return FromPawn->GetBaseAimRotation().Pitch;
	}
	
	//else this is different player, that need to get RemoteViewPitch instead
	const float Pitch = FRotator::DecompressAxisFromByte(FromPawn->RemoteViewPitch);
	return Pitch > 90 ? Pitch - 360 : Pitch;
}
