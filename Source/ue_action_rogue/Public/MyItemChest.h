// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "MyItemChest.generated.h"

UCLASS()
class UE_ACTION_ROGUE_API AMyItemChest : public AActor, public IMyGameplayInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AMyItemChest();

protected:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* LidMesh;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/// The Interact function from IMyGameplayInterface
	/// should use the _Implementation suffix since it is a BlueprintNativeEvent.
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;
};
