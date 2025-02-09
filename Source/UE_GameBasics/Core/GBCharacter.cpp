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

void AGBCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		//FRotator NewRotation = GetActorRotation();
		//NewRotation.Yaw = GetControlRotation().Yaw;
		//SetActorRotation(NewRotation);

		//AddMovementInput(GetActorForwardVector(), Value);

		// rotate character to face the direction of movement or move forward
		//
		////AddActorLocalRotation(FRotator(0.0f, GetControlRotation().Yaw, 0.0f));

		//GetCharacterMovement()->bOrientRotationToMovement = false;
		//GetCharacterMovement()->bUseControllerDesiredRotation = true;

		AddMovementInput(GetControlRotation().Vector(), Value);
	}
}

void AGBCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// Get right vector in standard of the Controller rotation

		FVector RightVector = FRotationMatrix(GetControlRotation()).GetScaledAxis(EAxis::Y);
		AddMovementInput(RightVector, Value);


		//FRotator NewRotation = GetActorRotation();
		//NewRotation.Yaw = GetControlRotation().Yaw;
		//SetActorRotation(NewRotation);

		////AddActorLocalRotation(FRotator(0.0f, GetControlRotation().Yaw, 0.0f));

		////GetCharacterMovement()->bOrientRotationToMovement = false;
		////GetCharacterMovement()->bUseControllerDesiredRotation = true;

		//AddMovementInput(GetActorRightVector(), Value);
	}
}

void AGBCharacter::Look(FVector2D Value)
{
	AddControllerYawInput(Value.X);
	AddControllerPitchInput(Value.Y);

	//RotateCamera(FRotator(0.0f, Value.X, 0.0f));
	//RotateCamera(FRotator(Value.Y, Value.X, 0.0f));
	//AddControllerPitchInput(Value.Y);
}

void AGBCharacter::Zoom(float Value)
{
	ZoomCamera(Value);
}

void AGBCharacter::RotateCamera(FRotator Value)
{
	//FRotator NewRotation = SpringArmComponent->GetRelativeRotation();
	FRotator NewRotation = SpringArmComponent->GetRelativeRotation();
	NewRotation.Yaw += Value.Yaw;
	NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + Value.Pitch, -80.0f, 80.0f);
	SpringArmComponent->SetRelativeRotation(NewRotation);
}

void AGBCharacter::ZoomCamera(float Value)
{
	SpringArmComponent->TargetArmLength = FMath::Clamp(SpringArmComponent->TargetArmLength + Value, 300.0f, 700.0f);
}

void AGBCharacter::TurnAroundAnimation(float Value)
{
	if (Value > 0)
	{
		IsTurningRight = true;
		IsTurningLeft = false;

		TurningYaw = Value;

		GetCharacterMovement()->bOrientRotationToMovement = false;
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
	}
	
	if (Value < 0)
	{
		IsTurningRight = false;
		IsTurningLeft = true;
		TurningYaw = Value;

		GetCharacterMovement()->bOrientRotationToMovement = false;
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
	}
}
