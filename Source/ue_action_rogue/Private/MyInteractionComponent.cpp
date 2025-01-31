// Source/ue_action_rogue/Private/MyInteractionComponent.cpp


#include "MyInteractionComponent.h"

#include "MyGameplayInterface.h"

// Sets default values for this component's properties
UMyInteractionComponent::UMyInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMyInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMyInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMyInteractionComponent::PrimaryInteract()
{
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	AActor* MyOwner = GetOwner();
	FVector EyeLocation;
	FRotator EyeRotation;
	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	const FVector End = EyeLocation + (EyeRotation.Vector()*1000);
	// FHitResult Hit;
	// GetWorld()->LineTraceSingleByObjectType(Hit, EyeLocation, End, ObjectQueryParams);

	TArray<FHitResult> Hits;
	FCollisionShape MyShape;
	MyShape.SetSphere(30.0f);

	const bool bBlockingHit = GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, End, FQuat::Identity, ObjectQueryParams, MyShape);
	const FColor LineColor = bBlockingHit ? FColor::Green : FColor::Red;
	for (FHitResult Hit : Hits)
	{
		if (AActor* HitActor = Hit.GetActor())
		{
			// e.g. MyItemChest implements IMyGameplayInterface
			if (HitActor->Implements<UMyGameplayInterface>())
			{
				APawn* MyPawn = Cast<APawn>(MyOwner);
				IMyGameplayInterface::Execute_Interact(HitActor, MyPawn);
				break;
			}
		}

		// for every hit we draw Sphere
		DrawDebugSphere(GetWorld(), Hit.ImpactPoint, 30.0f, 16, LineColor, false, 2.0f);
	}
	
	DrawDebugLine(GetWorld(), EyeLocation, End, LineColor, false, 2.0f, 0, 2.0f);
}

