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

public:
	void SetKeyBindingButton(FName Action, FKey Key);
	void UpdateText();
protected:
	virtual void NativeConstruct() override;
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

private:
	FName ActionName;
	FKey KeyBinding;

	bool IsWaitingForNewKey = false;

private:
	UFUNCTION()
	void OnKeyBindingButtonClicked();

	void SetKeyBinding(FKey NewKeyBinding);
};
