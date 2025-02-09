// Fill out your copyright notice in the Description page of Project Settings.

#include "GBPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"


AGBPlayerController::AGBPlayerController()
{
	SetInputMappings();
}

void AGBPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		InputSubsystem->AddMappingContext(MappingContext, 0);
	}
}

void AGBPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Bind the Enhanced Input Actions
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(IA_MoveForward, ETriggerEvent::Triggered, this, &AGBPlayerController::MoveForward);
		EnhancedInputComponent->BindAction(IA_MoveRight, ETriggerEvent::Triggered, this, &AGBPlayerController::MoveRight);
		EnhancedInputComponent->BindAction(IA_Jump, ETriggerEvent::Started, this, &AGBPlayerController::Jump);
		EnhancedInputComponent->BindAction(IA_Look, ETriggerEvent::Triggered, this, &AGBPlayerController::Look);
		EnhancedInputComponent->BindAction(IA_Zoom, ETriggerEvent::Triggered, this, &AGBPlayerController::Zoom);
		EnhancedInputComponent->BindAction(IA_ToggleWalkRun, ETriggerEvent::Started, this, &AGBPlayerController::ToggleWalkRun);
		EnhancedInputComponent->BindAction(IA_ToggleCrouch, ETriggerEvent::Started, this, &AGBPlayerController::ToggleCrouch);
	}

	// Bind the Axis
	InputComponent->BindAxis("Turn", this, &AGBPlayerController::AddYawInput);
	InputComponent->BindAxis("LookUp", this, &AGBPlayerController::AddPitchInput);
}

void AGBPlayerController::SetInputMappings()
{
	static ConstructorHelpers::FObjectFinder<class UInputMappingContext> IMC(TEXT("/Game/Core/Controllers/IMC_Player.IMC_Player"));
	if (IMC.Succeeded())
	{
		MappingContext = IMC.Object;
	}

	static ConstructorHelpers::FObjectFinder<class UInputAction> MoveForwardAction(TEXT("/Game/Core/Controllers/IA_MoveForward.IA_MoveForward"));
	if (MoveForwardAction.Succeeded())
	{
		IA_MoveForward = MoveForwardAction.Object;
	}

	static ConstructorHelpers::FObjectFinder<class UInputAction> MoveRightAction(TEXT("/Game/Core/Controllers/IA_MoveRight.IA_MoveRight"));
	if (MoveRightAction.Succeeded())
	{
		IA_MoveRight = MoveRightAction.Object;
	}

	static ConstructorHelpers::FObjectFinder<class UInputAction> JumpAction(TEXT("/Game/Core/Controllers/IA_Jump.IA_Jump"));
	if (JumpAction.Succeeded())
	{
		IA_Jump = JumpAction.Object;
	}

	static ConstructorHelpers::FObjectFinder<class UInputAction> LookAction(TEXT("/Game/Core/Controllers/IA_Look.IA_Look"));
	if (LookAction.Succeeded())
	{
		IA_Look = LookAction.Object;
	}

	static ConstructorHelpers::FObjectFinder<class UInputAction> ZoomAction(TEXT("/Game/Core/Controllers/IA_Zoom.IA_Zoom"));
	if (ZoomAction.Succeeded())
	{
		IA_Zoom = ZoomAction.Object;
	}

	static ConstructorHelpers::FObjectFinder<class UInputAction> ToggleWalkRunAction(TEXT("/Game/Core/Controllers/IA_ToggleWalkRun.IA_ToggleWalkRun"));
	if (ToggleWalkRunAction.Succeeded())
	{
		IA_ToggleWalkRun = ToggleWalkRunAction.Object;
	}

	static ConstructorHelpers::FObjectFinder<class UInputAction> ToggleCrouchAction(TEXT("/Game/Core/Controllers/IA_ToggleCrouch.IA_ToggleCrouch"));
	if (ToggleCrouchAction.Succeeded())
	{
		IA_ToggleCrouch = ToggleCrouchAction.Object;
	}
}

void AGBPlayerController::MoveForward(const FInputActionValue& Value)
{
	if (AGBCharacter* PlayerCharacter = Cast<AGBCharacter>(GetCharacter()))
	{
		PlayerCharacter->MoveForward(Value.Get<float>());
	}

}

void AGBPlayerController::MoveRight(const FInputActionValue& Value)
{
	if (AGBCharacter* PlayerCharacter = Cast<AGBCharacter>(GetCharacter()))
	{
		PlayerCharacter->MoveRight(Value.Get<float>());
	}
}

void AGBPlayerController::Jump(const FInputActionValue& Value)
{
	if (AGBCharacter* PlayerCharacter = Cast<AGBCharacter>(GetCharacter()))
	{
		PlayerCharacter->Jump();
	}
}

void AGBPlayerController::Look(const FInputActionValue& Value)
{
	if (AGBCharacter* PlayerCharacter = Cast<AGBCharacter>(GetCharacter()))
	{
		FVector2D LookValue = Value.Get<FVector2D>();
		LookValue.X *= YawSensitivity;
		LookValue.Y *= PitchSensitivity;
		PlayerCharacter->Look(LookValue);
	}
}

void AGBPlayerController::Zoom(const FInputActionValue& Value)
{
	if (AGBCharacter* PlayerCharacter = Cast<AGBCharacter>(GetCharacter()))
	{
		PlayerCharacter->Zoom(Value.Get<float>());
	}
}

void AGBPlayerController::ToggleWalkRun(const FInputActionValue& Value)
{
	if (AGBCharacter* PlayerCharacter = Cast<AGBCharacter>(GetCharacter()))
	{
		PlayerCharacter->ToggleWalkRun();
	}
}

void AGBPlayerController::ToggleCrouch(const FInputActionValue& Value)
{
	if (AGBCharacter* PlayerCharacter = Cast<AGBCharacter>(GetCharacter()))
	{
		PlayerCharacter->ToggleCrouch();
	}
}