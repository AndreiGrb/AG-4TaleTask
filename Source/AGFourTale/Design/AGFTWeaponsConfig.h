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
    , NumberOfProjectilesPerShot(1)
    , ProjectileRandomSpread(0.f)
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

    UPROPERTY(EditAnywhere, meta = (ClampMin = 1, EditCondition = "ShotType != EAGFTWeaponShotType::SHOT_SINGLE"))
    int32 NumberOfProjectilesPerShot;

    UPROPERTY(EditAnywhere, meta = (ClampMin = 0.f))
    float ProjectileRandomSpread;
};
