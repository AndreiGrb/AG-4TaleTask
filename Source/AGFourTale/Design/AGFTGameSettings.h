#pragma once

#include "AGFTGameSettings.generated.h"

class AHSFPWeapon;

UCLASS(Config = Game, defaultconfig)
class AGFOURTALE_API UAGFTGameSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	//Determines distance for trace, that is responsible for DynamicCrosshair position
	UPROPERTY(Config, EditAnywhere, Category = "UI", meta = (ClampMin = 1.f))
	float CrosshairTraceDistance = 10000.f;
	//Visualization of how Crosshair determines it's position on screen
	UPROPERTY(Config, EditAnywhere, Category = "UI")
	bool bShowCrosshairTrace;

	//Set all projectile life span
	UPROPERTY(Config, EditAnywhere, Category = "Projectile", meta = (ClampMin = 0.1f, ClampMax = 50.f))
	float ProjectileLifeSpan;

	//Time to unlock character's orientation after shooting
	UPROPERTY(Config, EditAnywhere, Category = "Character", meta = (ClampMin = 0.1f))
	float HipUnlockOrientationCooldown = 2.f;
	//MaxWalkSpeed while aiming
	UPROPERTY(Config, EditAnywhere, Category = "Character", meta = (ClampMin = 1.f))
	float MaxWalkSpeedAiming = 200.f;
	
private:
#if WITH_EDITOR
	virtual FText GetSectionText() const override { return FText::FromString(FString(TEXT("AG 4Tale"))); }
#endif
	virtual FName GetSectionName() const override { return FName(TEXT("AG 4Tale")); }
};