// Fill out your copyright notice in the Description page of Project Settings.

#include "GBHUD.h"
#include "UWPlayerKeyMapping.h"

AGBHUD::AGBHUD()
{
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FClassFinder<UUWPlayerKeyMapping> KeyBindingsWidgetBP(TEXT("/Game/Core/HUD/WBP_PlayerKeyMappingHUD.WBP_PlayerKeyMappingHUD_C"));
	if (KeyBindingsWidgetBP.Succeeded())
	{
		KeyBindingsWidgetClass = KeyBindingsWidgetBP.Class;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load KeyBindingsWidgetClass in AGBHUD::AGBHUD()"));
	}
}

void AGBHUD::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = GetOwningPlayerController();
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerController is null in AGBHUD::BeginPlay()"));
		return;
	}

	// Create the KeyBindings widget
	if (KeyBindingsWidgetClass)
	{
		KeyBindingsWidget = CreateWidget<UUWPlayerKeyMapping>(PlayerController, KeyBindingsWidgetClass);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("KeyBindingsWidgetClass is null in AGBHUD::BeginPlay()"));
	}

	// erase later
	if (KeyBindingsWidget)
	{
		KeyBindingsWidget->AddToViewport();
		KeyBindingsWidget->OpenKeyMapping();
	}
	//ShowKeyBindings();
}
