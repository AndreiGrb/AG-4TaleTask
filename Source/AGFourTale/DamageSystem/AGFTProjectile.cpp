#include "AGFTProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


AAGFTProjectile::AAGFTProjectile()
{
	SphereCollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereCollision");
	SetRootComponent(SphereCollisionComponent);
	
	ProjectileBodyComponent = CreateDefaultSubobject<UStaticMeshComponent>("ProjectileBody");
	ProjectileBodyComponent->SetupAttachment(SphereCollisionComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
}
