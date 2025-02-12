// Fill out your copyright notice in the Description page of Project Settings.

#include "GBPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "UserSettings/EnhancedInputUserSettings.h"
#include "EnhancedActionKeyMapping.h"
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
		InputSubsystem->GetUserSettings()->RegisterInputMappingContext(MappingContext);

		FModifyContextOptions Opts = {};
		Opts.bNotifyUserSettings = true;
		InputSubsystem->AddMappingContext(MappingContext, 0, Opts);
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
}

void AGBPlayerController::SetInputMappings()
{
	MappingContext = LoadObject<UInputMappingContext>(*IMCPath);
	IA_MoveForward = LoadObject<UInputAction>(*IA_MoveForwardPath);
	IA_MoveRight = LoadObject<UInputAction>(*IA_MoveRightPath);
	IA_Jump = LoadObject<UInputAction>(*IA_JumpPath);
	IA_Look = LoadObject<UInputAction>(*IA_LookPath);
	IA_Zoom = LoadObject<UInputAction>(*IA_ZoomPath);
	IA_ToggleWalkRun = LoadObject<UInputAction>(*IA_ToggleWalkRunPath);
	IA_ToggleCrouch = LoadObject<UInputAction>(*IA_ToggleCrouchPath);
}

template<typename T>
T* AGBPlayerController::LoadObject(const FString& Path)
{
	return Cast<T>(StaticLoadObject(T::StaticClass(), nullptr, *Path));
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

void AGBPlayerController::RebindActionKey(FName Action, const FKey FormerKey, const FKey NewKey)
{
	for (const FEnhancedActionKeyMapping& Mapping : MappingContext->GetMappings())
	{
		if (Mapping.Action.GetFName() == Action && Mapping.Key == FormerKey)
		{
			if (UEnhancedInputUserSettings* Settings = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer())->GetUserSettings())
			{
				FMapPlayerKeyArgs MapPlayerKeyArgs = {};
				MapPlayerKeyArgs.MappingName = Mapping.GetMappingName();
				MapPlayerKeyArgs.NewKey = Mapping.Key;
				MapPlayerKeyArgs.Slot = EPlayerMappableKeySlot::First;
				MapPlayerKeyArgs.NewKey = NewKey;

				FGameplayTagContainer TagContainer;
				Settings->UnMapPlayerKey(MapPlayerKeyArgs, TagContainer);

				MapPlayerKeyArgs.MappingName = Mapping.GetMappingName();
				Settings->MapPlayerKey(MapPlayerKeyArgs, TagContainer);

				return;
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Settings is null"));
			}
		}
	}
}

