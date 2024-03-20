#pragma once

#include "CoreMinimal.h"
#include "AGFourTale/Interfaces/AGFTPawnInterface.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "AGFTCharacter.generated.h"

class UAGFTHealthSystem;
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

	virtual void BeginPlay() override;

	float DefaultMaxWalkSpeed;


	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreReplication(IRepChangedPropertyTracker& ChangedPropertyTracker) override;

	FORCEINLINE virtual float GetRemoteViewYaw() const override { return RemoteViewYaw; }
	FORCEINLINE virtual void SetRemoteViewYaw(const float NewRemoteViewYaw) override
	{
		RemoteViewYaw = NewRemoteViewYaw;
	}

	virtual AAGFTWeapon* GetCurrentHoldingWeapon() const override;

	FORCEINLINE virtual bool IsAiming() const override { return bIsAiming; }

	
	UPROPERTY(VisibleAnywhere, Category = Camera, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;
	
	UPROPERTY(VisibleAnywhere, Category = Camera, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;

	UPROPERTY(VisibleAnywhere, Category = Camera, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> AimCameraBoom;

	UPROPERTY(VisibleAnywhere, Category = Camera, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> AimCamera;
	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UChildActorComponent> CurrentWeaponComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UChildActorComponent> SecondWeaponComponent;


	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAGFTHealthSystem> HealthComponent;

	
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
	
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> JumpAction;
	
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> MoveAction;
	
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> ShootAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> AimAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> SwitchWeaponAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> ReloadWeaponAction;

	
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);


	bool bIsSwitchingWeapons = false;
	bool bIsReloading = false;
	
	FORCEINLINE virtual bool CanShoot() const override { return !bIsSwitchingWeapons && !bIsReloading; }

	void ShootPressed();
	void ShootReleased();

	UFUNCTION(Server, Unreliable)
	void Server_Shoot(TSubclassOf<AAGFTWeapon> WeaponClass, const FVector& ShootLocation,
	                  const FRotator& ShootRotation);


	void AimPressed();
	void AimReleased();

	UFUNCTION(Server, Reliable)
	void Server_StartedAiming();

	UFUNCTION(Server, Reliable)
	void Server_StoppedAiming();

	void SetIsAiming(const bool NewAimingValue);

	UPROPERTY(Replicated)
	bool bIsAiming;
	
	
	//copy of RemoteViewPitch, but for Yaw
	UPROPERTY(Replicated)
	uint8 RemoteViewYaw;


	virtual bool IsOrientationLockActive() const override;

	UFUNCTION(Server, Unreliable)
	void Server_SetOrientationLocked();

	UFUNCTION(Server, Unreliable)
	void Server_SetOrientationUnlocked();

	void SetOrientationLock(bool bIsLocked);
	
	FTimerHandle OrientationLockTimerHandle;

	UFUNCTION()
	void OrientationLockTimer();

	
	void SwitchWeaponsPressed();

	virtual void SwitchWeapons() override;
	
	virtual void WeaponSwitchAnimComplete() override;

	UFUNCTION(Server, Reliable)
	void Server_SwitchWeapons();

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_SwitchWeapons();


	void ReloadWeaponPressed();

	virtual void ReloadWeapon() override;

	virtual void ReloadWeaponAnimComplete() override;

	UFUNCTION(Server, Reliable)
	void Server_ReloadWeapon();

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_ReloadWeapon();
};
