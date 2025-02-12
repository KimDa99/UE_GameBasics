// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"
#include "UWKeyBindingButton.generated.h"

/**
 * 
 */
UCLASS()
class UE_GAMEBASICS_API UUWKeyBindingButton : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite)
	UButton* KeyBindingButton;

	UPROPERTY(BlueprintReadWrite)
	UTextBlock* KeyBindingText;

private:
	FName ActionName;
	FKey KeyBinding;

	bool IsWaitingNewKey = false;
	TArray<FKey> KeysToIgnore = {EKeys::RightMouseButton, EKeys::LeftMouseButton};
	TArray<FKey> KeysToEscape = { EKeys::Escape };

public:
	void SetKeyBindingButton(FName Action, FKey Key);

private:
	UFUNCTION()
	void OnButtonClicked();

	void SetKeyBinding(FKey NewKeyBinding);

	void UpdateText();
protected:
	virtual void NativeConstruct() override;
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
};
