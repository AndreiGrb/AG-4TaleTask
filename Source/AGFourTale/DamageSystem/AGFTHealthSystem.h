#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AGFTHealthSystem.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDeath, AActor*, DeadActor, APlayerState*, Instigator);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class AGFOURTALE_API UAGFTHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	FOnDeath OnDeath;
	FORCEINLINE bool IsDead() const { return bIsDead; }

	void Revive();

	void ReceiveDamage(const float Damage, APlayerState* Instigator = nullptr);

	FORCEINLINE int32 GetCurrentHealth() const { return Health; }
	
private:
	virtual void BeginPlay() override;

	int32 DefaultHealthValue;
	
	UPROPERTY(EditAnywhere, Category = "Settings")
	int32 Health = 100.f;

	bool bIsDead;

	TWeakObjectPtr<APlayerState> Killer;
};
