// Fill out your copyright notice in the Description page of Project Settings.


#include "MyItemChest.h"

// Sets default values
AMyItemChest::AMyItemChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;

	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LidMesh"));
	LidMesh->SetupAttachment(BaseMesh);
}

// Called when the game starts or when spawned
void AMyItemChest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	LidMesh->SetRelativeRotation(FRotator(90, 0, 0));
}
