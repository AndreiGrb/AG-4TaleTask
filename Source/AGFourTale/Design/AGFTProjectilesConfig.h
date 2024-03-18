#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "AGFTProjectilesConfig.generated.h"

class AAGFTProjectile;

USTRUCT(BlueprintType)
struct FAGFTProjectileConfig : public FTableRowBase
{
    GENERATED_BODY()

public:
    FAGFTProjectileConfig()
    : Damage(35.f)
    {}
    
    UPROPERTY(EditAnywhere, meta = (ClampMin = 0.f))
    float Damage;
};