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

	if (KeyBindingButton)
	{
		KeyBindingButton->OnClicked.AddDynamic(this, &UUWKeyBindingButton::OnKeyBindingButtonClicked);
		UpdateText();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("KeyBindingButton is null in UUWKeyBindingButton::NativeConstruct()"));
	}
}

void UUWKeyBindingButton::UpdateText()
{
	if (!KeyBindingText)
	{
		UE_LOG(LogTemp, Error, TEXT("KeyBindingText is null in UUWKeyBindingButton::UpdateText()"));
		return;
	}
	
	if (IsWaitingForNewKey)
	{
		KeyBindingText->SetText(FText::FromString(TEXT("Press a key")));
		return;
	}
	else
	{
		KeyBindingText->SetText(FText::FromString(KeyBinding.GetDisplayName().ToString()));
	}
}

FReply UUWKeyBindingButton::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (IsWaitingForNewKey)
	{
		FKey PressedKey = InKeyEvent.GetKey();

		if (PressedKey == EKeys::Escape)
		{
			IsWaitingForNewKey = false;
			UpdateText();
			return FReply::Handled();
		}

		if (PressedKey == EKeys::LeftMouseButton || PressedKey == EKeys::RightMouseButton)
		{
			return FReply::Handled();
		}

		SetKeyBinding(PressedKey);

		IsWaitingForNewKey = false;

		return FReply::Handled();
	}

	return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}

void UUWKeyBindingButton::OnKeyBindingButtonClicked()
{
	IsWaitingForNewKey = true;
	UpdateText();

}

void UUWKeyBindingButton::SetKeyBinding(FKey NewKeyBinding)
{
	// Array to store existing modifiers
	APlayerController* PlayerController = GetOwningPlayer();
	Cast<AGBPlayerController>(PlayerController)->RebindActionKey(ActionName, KeyBinding, NewKeyBinding);
	KeyBinding = NewKeyBinding;
	IsWaitingForNewKey = false;
	UpdateText();
}