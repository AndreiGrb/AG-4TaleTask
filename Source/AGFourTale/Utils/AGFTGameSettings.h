#pragma once

#include "AGFTGameSettings.generated.h"

class AHSFPWeapon;

UCLASS(Config = Game, defaultconfig)
class AGFOURTALE_API UAGFTGameSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	//Determines distance for trace, that is responsible for DynamicCrosshair position
	UPROPERTY(Config, EditAnywhere, Category = "UI")
	float CrosshairTraceDistance = 10000.f;
	
	
private:
#if WITH_EDITOR
	virtual FText GetSectionText() const override { return FText::FromString(FString(TEXT("AG 4Tale"))); }
#endif
	virtual FName GetSectionName() const override { return FName(TEXT("AG 4Tale")); }
};