// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/HorizontalBox.h"
#include "UWPlayerKeyMapping.generated.h"

/**
 * 
 */
UCLASS()
class UE_GAMEBASICS_API UUWPlayerKeyMapping : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual bool Initialize() override;

	void NativeConstruct();


private:
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UUWKeyBindingButton> KeyBindingButtonClass;

	double KeyMappingRowSpacing = 10;

protected:
	UPROPERTY(BlueprintReadWrite)
	UVerticalBox* KeyMappingContainer;

	UPROPERTY(BlueprintReadWrite)
	UButton* ExitButton;

private:
	void SetKeyMapping();

	void AddRow(const struct FEnhancedActionKeyMapping& Map);

public:
	UFUNCTION(BlueprintCallable)
	void OpenKeyMapping();

	UFUNCTION(BlueprintCallable)
	void OnExitButtonClicked();
};

