// Fill out your copyright notice in the Description page of Project Settings.


#include "GBCharacter.h"

// Sets default values
AGBCharacter::AGBCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SetupSpringArm();
	SetupCamera();
	SetupMesh();

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimBP(*AnimBPPath);
	if (!AnimBP.Succeeded())
	{
		UE_LOG(LogTemp, Warning, TEXT("Animation Blueprint not found!"));
		return;
	}
	GetMesh()->SetAnimInstanceClass(AnimBP.Class);

	SetupCharacterMovement();
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
		UnCrouch();
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

void AGBCharacter::SetupSpringArm()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 500.0f;
	SpringArmComponent->bUsePawnControlRotation = true;
}

void AGBCharacter::SetupCamera()
{
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 40.0f));
	CameraComponent->bUsePawnControlRotation = true;
}

void AGBCharacter::SetupMesh()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(*MeshPath);
	if (MeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
	}

	// Set Mesh Transform
	GetMesh()->SetupAttachment(RootComponent);
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
}

void AGBCharacter::SetupCharacterMovement()
{
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;

	GetCharacterMovement()->RotationRate = FRotator(0.0f, 360.0f, 0.0f);

	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
}
