// Fill out your copyright notice in the Description page of Project Settings.


#include "GBCharacter.h"

// Sets default values
AGBCharacter::AGBCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set Spring Arm Component
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 500.0f;
	SpringArmComponent->bUsePawnControlRotation = true;
	//SpringArmComponent->bUsePawnControlRotation = false;

	// Set Camera Component
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 40.0f));
	CameraComponent->bUsePawnControlRotation = true;
	//CameraComponent->bUsePawnControlRotation = false;

	// Set Defaylt Skeletal Mesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Game/Characters/Mannequins/Meshes/SKM_Quinn.SKM_Quinn"));
	if (MeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
	}

	// Set Mesh Transform
	GetMesh()->SetupAttachment(RootComponent);
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));


	// Set Animation Blueprint
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimBP(TEXT("/Game/Characters/Mannequins/Animations/ABP_Quinn.ABP_Quinn_C"));
	if (AnimBP.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(AnimBP.Class);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Animation Blueprint not found!"));
	}

	// Set Character Movement
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;

	GetCharacterMovement()->RotationRate = FRotator(0.0f, 360.0f, 0.0f);

	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
}

// Called when the game starts or when spawned
void AGBCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGBCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGBCharacter::ToggleWalkRun()
{
	if (GetCharacterMovement()->MaxWalkSpeed == 600.0f)
	{
		GetCharacterMovement()->MaxWalkSpeed = 230.0f;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	}
}

void AGBCharacter::ToggleCrouch()
{
	if (GetCharacterMovement()->bWantsToCrouch)
	{
		UnCrouch();
		GetCharacterMovement()->MaxWalkSpeed = 230.0f;
	}
	else
	{
		Crouch();
		//speed
		GetCharacterMovement()->MaxWalkSpeedCrouched = 120.0f;
	}
}

void AGBCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		AddMovementInput(GetControlRotation().Vector(), Value);
	}
}

void AGBCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		FVector RightVector = FRotationMatrix(GetControlRotation()).GetScaledAxis(EAxis::Y);
		AddMovementInput(RightVector, Value);
	}
}

void AGBCharacter::Look(FVector2D Value)
{
	AddControllerYawInput(Value.X);
	AddControllerPitchInput(Value.Y);
}

void AGBCharacter::Zoom(float Value)
{
	ZoomCamera(Value);
}

void AGBCharacter::ZoomCamera(float Value)
{
	SpringArmComponent->TargetArmLength = FMath::Clamp(SpringArmComponent->TargetArmLength + Value, 300.0f, 700.0f);
}