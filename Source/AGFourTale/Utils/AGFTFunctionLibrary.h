#pragma once

DECLARE_LOG_CATEGORY_EXTERN(LogUtils, Log, All);

struct FAGFTUtils
{
public:
	static float GetReplicatedPitchValue(const APawn* FromPawn);
	static float GetReplicatedYawValue(const APawn* FromPawn);
};