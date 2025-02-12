// Fill out your copyright notice in the Description page of Project Settings.


#include "UWKeyBindingButton.h"
#include "UE_GameBasics/Core/GBPlayerController.h"

void UUWKeyBindingButton::SetKeyBindingButton(FName Action, FKey Key)
{
	ActionName = Action;
	KeyBinding = Key;	
}

void UUWKeyBindingButton::NativeConstruct()
{
	Super::NativeConstruct();

	if (!KeyBindingButton)
	{
		UE_LOG(LogTemp, Error, TEXT("KeyBindingButton is null in UUWKeyBindingButton::NativeConstruct()"));
	}

	KeyBindingButton->OnClicked.AddDynamic(this, &UUWKeyBindingButton::OnButtonClicked);
	UpdateText();
}

void UUWKeyBindingButton::UpdateText()
{
	if (!KeyBindingText)
	{
		UE_LOG(LogTemp, Error, TEXT("KeyBindingText is null in UUWKeyBindingButton::UpdateText()"));
		return;
	}

	FText BindingText = (IsWaitingNewKey) ? FText::FromString("Press a Key") : KeyBinding.GetDisplayName();
	KeyBindingText->SetText(BindingText);
}

FReply UUWKeyBindingButton::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (IsWaitingNewKey)
	{
		FKey PressedKey = InKeyEvent.GetKey();

		if (KeysToIgnore.Contains(PressedKey))
		{
			return FReply::Handled();
		}

		IsWaitingNewKey = false;
		if (KeysToEscape.Contains(PressedKey))
		{			
			UpdateText();
			return FReply::Handled();
		}

		SetKeyBinding(PressedKey);
		UpdateText();

		return FReply::Handled();
	}

	return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}

void UUWKeyBindingButton::OnButtonClicked()
{
	IsWaitingNewKey = true;
	UpdateText();
}

void UUWKeyBindingButton::SetKeyBinding(FKey NewKeyBinding)
{
	if (APlayerController* PC = GetOwningPlayer())
	{
		Cast<AGBPlayerController>(PC)->RebindActionKey(ActionName, KeyBinding, NewKeyBinding);
		KeyBinding = NewKeyBinding;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerController is null in UUWKeyBindingButton::SetKeyBinding()"));
	}
}