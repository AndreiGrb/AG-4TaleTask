#include "AGFTCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "AGFourTale/DamageSystem/AGFTWeapon.h"
#include "AGFourTale/Utils/AGFTLogCategories.h"
#include "AGFourTale/Utils/AGFTNames.h"
#include "Net/UnrealNetwork.h"


AAGFTCharacter::AAGFTCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;	
	CameraBoom->bUsePawnControlRotation = true;
	
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	CurrentWeaponComponent = CreateDefaultSubobject<UChildActorComponent>("CurrentWeapon");
	CurrentWeaponComponent->SetupAttachment(GetMesh(), SOCKETNAME_WEAPON_ATTACHMENT);
}

void AAGFTCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (const auto EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAGFTCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AAGFTCharacter::Look);

		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Started, this, &AAGFTCharacter::ShootPressed);
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Completed, this, &AAGFTCharacter::ShootReleased);
	}
	else
	{
		UE_LOG(LogCharacter, Error, TEXT("[AAGFTCharacter::SetupPlayerInputComponent]'%s'"
								   " Failed to find an Enhanced Input component!"), *GetNameSafe(this));
	}

	if (const auto PlayerController = Cast<APlayerController>(Controller))
	{
		if (const auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
}

void AAGFTCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(AAGFTCharacter, RemoteViewYaw, COND_SkipOwner);
}

void AAGFTCharacter::PreReplication(IRepChangedPropertyTracker& ChangedPropertyTracker)
{
	Super::PreReplication(ChangedPropertyTracker);

	if (GetLocalRole() == ROLE_Authority && GetController())
	{
		// Compress yaw to 1 byte
		SetRemoteViewYaw(FRotator::CompressAxisToByte(GetController()->GetControlRotation().Yaw));
	}
}

AAGFTWeapon* AAGFTCharacter::GetCurrentHoldingWeapon()
{
	return Cast<AAGFTWeapon>(CurrentWeaponComponent->GetChildActor());
}

void AAGFTCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AAGFTCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AAGFTCharacter::ShootPressed()
{
	AAGFTWeapon* Weapon = GetCurrentHoldingWeapon();
	if (!IsValid(Weapon))
	{
		UE_LOG(LogCharacter, Error, TEXT("[AAGFTCharacter::ShootPressed] No weapon is currently hold"));
		return;
	}

	Weapon->OnWeaponFired.AddDynamic(this, &AAGFTCharacter::Server_Shoot);
	Weapon->ShootPressed();
}

void AAGFTCharacter::ShootReleased()
{
	AAGFTWeapon* Weapon = GetCurrentHoldingWeapon();
	if (!IsValid(Weapon))
	{
		UE_LOG(LogCharacter, Error, TEXT("[AAGFTCharacter::ShootReleased] No weapon is currently hold"));
		return;
	}

	Weapon->OnWeaponFired.RemoveDynamic(this, &AAGFTCharacter::Server_Shoot);
	Weapon->ShootReleased();
}

void AAGFTCharacter::Server_Shoot_Implementation(TSubclassOf<AAGFTWeapon> WeaponClass,
                                                 const FVector& ShootLocation, const FRotator& ShootRotation)
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = GetOwner();
	
	AAGFTWeapon* CreatedWeapon = GetWorld()->SpawnActor<AAGFTWeapon>(WeaponClass, ShootLocation, ShootRotation, SpawnParameters);
	if (!CreatedWeapon)
	{
		UE_LOG(LogCharacter, Error, TEXT("[AAGFTCharacter::Server_Shoot] Failed to spawn server shooter"));
		return;
	}
	CreatedWeapon->SetActorHiddenInGame(true);
	CreatedWeapon->SetActorEnableCollision(false);
	CreatedWeapon->DisableComponentsSimulatePhysics();
	CreatedWeapon->SetLifeSpan(0.1f);
	
	CreatedWeapon->ShootProjectile(ShootLocation, ShootRotation);
}
