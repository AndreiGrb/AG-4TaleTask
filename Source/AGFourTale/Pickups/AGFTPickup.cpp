#include "AGFTPickup.h"

#include "AGFourTale/Design/AGFTGameSettings.h"
#include "Components/SphereComponent.h"


AAGFTPickup::AAGFTPickup()
{
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	SetRootComponent(DefaultSceneComponent);

	const FVector RelativeOffset = FVector(0.f, 0.f, 100.f);
	
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollision->SetupAttachment(RootComponent);
	SphereCollision->SetSphereRadius(75.f);
	SphereCollision->SetRelativeLocation(RelativeOffset);
	
	PickupActorComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("PickupActor"));
	PickupActorComponent->SetupAttachment(RootComponent);
	PickupActorComponent->SetRelativeLocation(RelativeOffset);
}

void AAGFTPickup::BeginPlay()
{
	Super::BeginPlay();

	if (PickupActorComponent->GetChildActor())
	{
		PickupActorComponent->GetChildActor()->SetActorEnableCollision(false);
	}

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AAGFTPickup::OnSphereOverlap);
}

void AAGFTPickup::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	const float SpinSpeed = DeltaSeconds * GetDefault<UAGFTGameSettings>()->PickupSpinSpeed;
	PickupActorComponent->AddWorldRotation(FRotator(0.f, SpinSpeed, 0.f));
}

void AAGFTPickup::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}
