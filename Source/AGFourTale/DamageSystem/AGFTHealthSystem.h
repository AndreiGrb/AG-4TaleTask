#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AGFTHealthSystem.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class AGFOURTALE_API UAGFTHealthSystem : public UActorComponent
{
	GENERATED_BODY()

public:
	FOnDeath OnDeath;

	void ReceiveDamage(const float Damage);
	
private:
	UPROPERTY(EditAnywhere, Category = "Settings")
	int32 Health;
};
