#pragma once

#include "CoreMinimal.h"
#include "AGFourTale/Interfaces/AGFTPawnInterface.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "AGFTCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;


UCLASS(config=Game)
class AAGFTCharacter : public ACharacter, public IAGFTPawnInterface
{
	GENERATED_BODY()
	
public:
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

private:
	AAGFTCharacter();

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;


	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreReplication(IRepChangedPropertyTracker& ChangedPropertyTracker) override;

	FORCEINLINE virtual float GetRemoteViewYaw() const override { return RemoteViewYaw; }
	FORCEINLINE virtual void SetRemoteViewYaw(const float NewRemoteViewYaw) override
	{
		RemoteViewYaw = NewRemoteViewYaw;
	}

	virtual AAGFTWeapon* GetCurrentHoldingWeapon() override;

	
	UPROPERTY(VisibleAnywhere, Category = Camera)
	TObjectPtr<USpringArmComponent> CameraBoom;
	
	UPROPERTY(VisibleAnywhere, Category = Camera)
	TObjectPtr<UCameraComponent> FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UChildActorComponent> CurrentWeaponComponent;

	
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
	
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> JumpAction;
	
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> MoveAction;
	
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> LookAction;

	
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	
	//copy of RemoteViewPitch, but for Yaw
	UPROPERTY(Replicated)
	uint8 RemoteViewYaw;
};

