#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AGFTWeapon.generated.h"

UCLASS()
class AGFOURTALE_API AAGFTWeapon : public AActor
{
	GENERATED_BODY()

private:
	AAGFTWeapon();
	
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> WeaponMeshComponent;
};
