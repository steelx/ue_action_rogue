// MyMagicProjectile.cpp
#include "MyMagicProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AMyMagicProjectile::AMyMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// IMPORTANT
	// Project Settings - Engine -> Collisions select Projectile preset that we created
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetVisibility(!bDebugSphere);
	RootComponent = SphereComp;

    EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(SphereComp);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->InitialSpeed = 1000.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;
	MovementComp->ProjectileGravityScale = 0.0f;// moves in straight line

	bDebugSphere = true;
	HitActor = nullptr;
	SphereComp->OnComponentHit.AddDynamic(this, &AMyMagicProjectile::OnSphereHit);

	// This line crashing game
	// GetWorldTimerManager().SetTimer(DestroyTimerHandle, this, &AMyMagicProjectile::DestroyTimerCallback, 3.0f);
}

void AMyMagicProjectile::OnSphereHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor != GetInstigator())
	{
		HitActor = OtherActor;

		if (ImpactEffect)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, 
				Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
		}

		GetWorldTimerManager().ClearTimer(DestroyTimerHandle);
		Destroy();
	}
}


void AMyMagicProjectile::DestroyTimerCallback()
{
	if (!HitActor)
	{
		Destroy();
	}
}

// Called when the game starts or when spawned
void AMyMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Draw debug sphere if debug is enabled
	if (bDebugSphere)
	{
		DrawDebugSphere(GetWorld(), GetActorLocation(), SphereComp->GetScaledSphereRadius(), 32,
			FColor::Green, false, -1.0f, 0, 1.0f);
	}
}

