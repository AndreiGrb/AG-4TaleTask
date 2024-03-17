#include "AGFTFunctionLibrary.h"

#include "AGFourTale/Interfaces/AGFTPawnInterface.h"

DEFINE_LOG_CATEGORY(LogUtils);


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

float FAGFTUtils::GetReplicatedYawValue(const APawn* FromPawn)
{
	if (!IsValid(FromPawn))
	{
		return 0.f;
	}
	if (FromPawn->GetController() && FromPawn->IsLocallyControlled())
	{
		return FromPawn->GetBaseAimRotation().Yaw;
	}
	
	//else this is different player, that need to get RemoteViewYaw instead
	if (const auto PawnInterface = Cast<IAGFTPawnInterface>(FromPawn))
	{
		return FRotator::DecompressAxisFromByte(PawnInterface->GetRemoteViewYaw());
	}
	//if pawn not inherited by interface, write message in log and return 0.f
	UE_LOG(LogUtils, Error, TEXT("[FAGFTUtils::GetReplicatedYawValue] Pawn is not inherited by interface"
							  " and can't return RemoteViewYaw"));
	return 0.f;
}
