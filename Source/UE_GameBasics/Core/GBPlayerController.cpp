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
}

void AGBPlayerController::SetupInputComponent()
{
}

void AGBPlayerController::SetInputMappings()
{
	static ConstructorHelpers::FObjectFinder<class UInputMappingContext> IMC(TEXT("/Game/Core/Controllers/IMC_Player.IMC_Player"));
	if (IMC.Succeeded())
	{
		DefaultMappingContext = IMC.Object;
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

}
