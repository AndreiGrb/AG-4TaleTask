#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "AGFTWeaponsConfig.generated.h"

class AAGFTProjectile;


UENUM(BlueprintType)
enum class EAGFTWeaponShotType : uint8
{
    SHOT_SINGLE UMETA(DisplayName = "Single"),
    SHOT_SHOTGUN UMETA(DisplayName = "Shotgun"),
    MAX UMETA(Hidden)
};

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
    , ShotType(EAGFTWeaponShotType::SHOT_SINGLE)
    , NumberOfProjectiles(1)
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

    UPROPERTY(EditAnywhere)
    EAGFTWeaponShotType ShotType;

    UPROPERTY(EditAnywhere, meta = (ClampMin = 1, EditCondition = "ShotType != EAGFTWeaponShotType::SHOT_SINGLE"))
    int32 NumberOfProjectiles;
};