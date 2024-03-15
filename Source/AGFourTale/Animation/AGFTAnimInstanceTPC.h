#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimInstanceProxy.h"
#include "AGFTAnimInstanceTPC.generated.h"


class UCharacterMovementComponent;

USTRUCT(BlueprintType)
struct FAGFTAnimInstanceTPC_Proxy : public FAnimInstanceProxy
{
	GENERATED_BODY()

public:
	FAGFTAnimInstanceTPC_Proxy() {}
	FAGFTAnimInstanceTPC_Proxy(UAnimInstance* Instance) {}

private:
	virtual void PreUpdate(UAnimInstance* InAnimInstance, float DeltaSeconds) override;
	void UpdateValuesFromAnimInstance(const class UAGFTAnimInstanceTPC* InAnimInstance);

#pragma region PreUpdate variables (directly from AnimInstance)
	
#pragma endregion
	
	virtual void Update(float DeltaSeconds) override;
	void CalculateValuesInProxy(const float DeltaSeconds);

	bool bShouldUpdate = true;

#pragma region Update variables (in anim thread)
	
#pragma endregion
};

UCLASS()
class AGFOURTALE_API UAGFTAnimInstanceTPC : public UAnimInstance
{
	GENERATED_BODY()

private:
	virtual void NativeInitializeAnimation() override;

	
	UPROPERTY(Transient, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FAGFTAnimInstanceTPC_Proxy Proxy;

	virtual FAnimInstanceProxy* CreateAnimInstanceProxy() override { return &Proxy; }
	virtual void DestroyAnimInstanceProxy(FAnimInstanceProxy* InProxy) override {}

	friend struct FAGFTAnimInstanceTPC_Proxy;


	UPROPERTY(Transient, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ACharacter> CharacterOwner;
	UPROPERTY(Transient, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCharacterMovementComponent> MovementComponent;
};
