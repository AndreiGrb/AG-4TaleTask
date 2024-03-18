#include "AGFTProjectile.h"

#include "AGFourTale/Design/AGFTGameSettings.h"
#include "AGFourTale/Utils/AGFTNames.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"


AAGFTProjectile::AAGFTProjectile()
{
	SphereCollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereCollision");
	SetRootComponent(SphereCollisionComponent);
	SphereCollisionComponent->SetCollisionProfileName(COLLISION_PROFILENAME_PROJECTILE);
	SphereCollisionComponent->SetRelativeScale3D(FVector(0.1675f));
	
	ProjectileBodyComponent = CreateDefaultSubobject<UStaticMeshComponent>("ProjectileBody");
	ProjectileBodyComponent->SetupAttachment(SphereCollisionComponent);
	ProjectileBodyComponent->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	ProjectileBodyComponent->SetRelativeScale3D(FVector(0.195f));

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovementComponent->InitialSpeed = 3000.f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;

	bReplicates = true;
}

void AAGFTProjectile::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(GetDefault<UAGFTGameSettings>()->ProjectileLifeSpan);

	const auto PlayerController = Cast<APlayerController>(GetOwner());
	if (PlayerController && PlayerController->IsLocalController())
	{	//Hide replicated projectile for owner
		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
	}

	SphereCollisionComponent->OnComponentHit.AddDynamic(this, &AAGFTProjectile::OnProjectileHit);
}

void AAGFTProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Destroy();
}
