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
	UPROPERTY(Transient, BlueprintReadOnly, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	bool bIsFalling = false;

	UPROPERTY(Transient, BlueprintReadOnly, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	bool bIsAiming = false;

	FVector Velocity = FVector::ZeroVector;
	FVector CurrentAcceleration = FVector::ZeroVector;
	float MoveThreshold = 0.f;
	float FallVelocityThreshold = 0.f;
	
	FRotator BaseActorRotation = FRotator::ZeroRotator;
	float BaseYawAim = 0.f;
	float PitchAim = 0.f;
#pragma endregion
	
	virtual void Update(float DeltaSeconds) override;
	void CalculateValuesInProxy(const float DeltaSeconds);

	bool bShouldUpdate = true;

#pragma region Update variables (in anim thread)
	UPROPERTY(Transient, BlueprintReadOnly, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float GroundSpeed = 0.f;

	UPROPERTY(Transient, BlueprintReadOnly, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	bool bShouldMove = false;

	UPROPERTY(Transient, BlueprintReadOnly, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	bool bCanEnterJumpFromFalling = false;

	UPROPERTY(Transient, BlueprintReadOnly, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float MoveDirection = 0.f;

	UPROPERTY(Transient, BlueprintReadOnly, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	FRotator AimRotation = FRotator::ZeroRotator;
#pragma endregion
};

UCLASS()
class AGFOURTALE_API UAGFTAnimInstanceTPC : public UAnimInstance
{
	GENERATED_BODY()

private:
	virtual void NativeInitializeAnimation() override;

	//Should not be changed in Details. Only for change in Preview
	UPROPERTY(Transient, BlueprintReadOnly, EditAnywhere, Category = "Settings|AnimProxy Preview", meta = (AllowPrivateAccess = "true"))
	FAGFTAnimInstanceTPC_Proxy Proxy;

	virtual FAnimInstanceProxy* CreateAnimInstanceProxy() override { return &Proxy; }
	virtual void DestroyAnimInstanceProxy(FAnimInstanceProxy* InProxy) override {}

	friend struct FAGFTAnimInstanceTPC_Proxy;


	UPROPERTY(Transient, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ACharacter> CharacterOwner;
	UPROPERTY(Transient, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCharacterMovementComponent> MovementComponent;

	//Used in calculation for Proxy's bShouldMove. Determines threshold for value GroundSpeed 
	UPROPERTY(EditAnywhere, Category = "Settings", meta = (ClampMin = 0.1f))
	float MoveThreshold = 3.f;

	//Used in calculation for Proxy's bCanEnterJumpFromFalling. Determines threshold for Z value of Velocity
	UPROPERTY(EditAnywhere, Category = "Settings", meta = (ClampMin = 0.1f))
	float FallVelocityThreshold = 100.f;
};
