#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "AGFTWeaponsConfig.generated.h"

class AAGFTProjectile;

USTRUCT(BlueprintType)
struct FAGFTWeaponConfig : public FTableRowBase
{
    GENERATED_BODY()

public:
    FAGFTWeaponConfig()
    : bIsAutomatic(false)
    , FireRate(1.f)
    , MaxAmmoCapacity(1)
    , ProjectileClass(nullptr)
    {}
    
    UPROPERTY(EditAnywhere)
    bool bIsAutomatic;

    //Seconds between each shot
    UPROPERTY(EditAnywhere, meta = (ClampMin = 0.1f))
    float FireRate;

    UPROPERTY(EditAnywhere)
    int32 MaxAmmoCapacity;

    UPROPERTY(EditAnywhere)
    TSubclassOf<AAGFTProjectile> ProjectileClass;
};