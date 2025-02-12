// Fill out your copyright notice in the Description page of Project Settings.

#include "UWPlayerKeyMapping.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "UE_GameBasics/Core/GBPlayerController.h"
#include "UE_GameBasics/Core/HUD/UWKeyBindingButton.h"
#include "Components/Spacer.h"
#include "InputMappingContext.h"

bool UUWPlayerKeyMapping::Initialize()
{
	Super::Initialize();

	if (ExitButton)
	{
		ExitButton->OnClicked.AddDynamic(this, &UUWPlayerKeyMapping::OnExitButtonClicked);
	}

	return false;
}

void UUWPlayerKeyMapping::NativeConstruct()
{
	Super::NativeConstruct();
	SetKeyMapping();
}

void UUWPlayerKeyMapping::SetKeyMapping()
{
	APlayerController* PC = GetOwningPlayer();
	if (!PC)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerController is null in UUWPlayerKeyMapping::SetKeyMapping()"));
		return;
	}

	UInputMappingContext* const MappingContext = Cast<AGBPlayerController>(PC)->GetMappingContext();

	for (const FEnhancedActionKeyMapping& Map : MappingContext->GetMappings())
	{
		// Skip the None mappings
		if (Map.GetMappingName() == "None")
		{
			continue;
		}

		AddRow(Map);
	}
}

void UUWPlayerKeyMapping::AddRow(const FEnhancedActionKeyMapping& Map)
{
	UHorizontalBox* Row = NewObject<UHorizontalBox>(this);
	KeyMappingContainer->AddChild(Row);

	UTextBlock* ActionName = NewObject<UTextBlock>(this);
	ActionName->SetText(FText::FromName(Map.GetMappingName()));
	Row->AddChild(ActionName);

	USpacer* Spacer = NewObject<USpacer>(this);
	Spacer->SetSize(FVector2D(KeyMappingRowSpacing, 0));
	Row->AddChild(Spacer);

	UUWKeyBindingButton* RebindButton = NewObject<UUWKeyBindingButton>(this, KeyBindingButtonClass);
	RebindButton->SetKeyBindingButton(Map.Action.GetFName(), Map.Key);
	Row->AddChild(RebindButton);
}

void UUWPlayerKeyMapping::OpenKeyMapping()
{
	SetVisibility(ESlateVisibility::Visible);
}

void UUWPlayerKeyMapping::OnExitButtonClicked()
{
	SetVisibility(ESlateVisibility::Collapsed);
}