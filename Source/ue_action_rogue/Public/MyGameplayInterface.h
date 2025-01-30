// MyGameplayInterface.h

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MyGameplayInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMyGameplayInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UE_ACTION_ROGUE_API IMyGameplayInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	/// while adding use name Interact_Implementation
	UFUNCTION(BlueprintNativeEvent)
	void Interact(APawn* InstigatorPawn);
};
