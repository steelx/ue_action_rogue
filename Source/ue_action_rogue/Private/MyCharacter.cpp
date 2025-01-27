// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "ue_action_rogue/Public/MyCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("Spring Arm Component");
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>("Camera Component");
	CameraComp->SetupAttachment(SpringArmComp);
	// RPG like camera, character won't rotation only camera does if set to false
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &AMyCharacter::PrimaryAttack);
}

void AMyCharacter::MoveForward(const float Value)
{
	if (Value != 0.0f)
	{
		// move with camera rotation
		FRotator ControlRot = GetControlRotation();
		ControlRot.Pitch = 0.0f;
		ControlRot.Roll = 0.0f;
		AddMovementInput(ControlRot.Vector(), Value);

		// Update the character's rotation to face the movement direction
		const FRotator NewRotation(0.0f, ControlRot.Yaw, 0.0f);
		SetActorRotation(NewRotation);
	}
}

void AMyCharacter::MoveRight(const float Value)
{
	if (Value != 0.0f)
	{
		FRotator ControlRot = GetControlRotation();
		ControlRot.Pitch = 0.0f;
		ControlRot.Roll = 0.0f;
		// X = Forward (Red), Y = Right (Green), Z = Up (Blue)
		const FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);
		AddMovementInput(RightVector, Value);

		// Update the character's rotation to face the movement direction
		const FRotator NewRotation(0.0f, ControlRot.Yaw, 0.0f);
		SetActorRotation(NewRotation);
	}
}

void AMyCharacter::PrimaryAttack()
{
	if (ProjectileClass)
	{
		FTransform SpawnTransform = FTransform(GetActorRotation(), GetActorLocation());
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        
		GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTransform, SpawnParams);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ProjectileClass is not set in %s"), *GetNameSafe(this));
	}
}
