// Fill out your copyright notice in the Description page of Project Settings.

#include "GBHUD.h"
#include "UWPlayerKeyMapping.h"

AGBHUD::AGBHUD()
{
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FClassFinder<UUWPlayerKeyMapping> KeyBindingsWidgetBP(*KeyBindingsWidgetPath);
	if (!KeyBindingsWidgetBP.Succeeded())
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load KeyBindingsWidgetClass in AGBHUD::AGBHUD()"));
		return;
	}
	KeyBindingsWidgetClass = KeyBindingsWidgetBP.Class;
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

	if (!KeyBindingsWidgetClass)
	{
		UE_LOG(LogTemp, Error, TEXT("KeyBindingsWidgetClass is null in AGBHUD::BeginPlay()"));
		return;
	}
	KeyBindingsWidget = CreateWidget<UUWPlayerKeyMapping>(PlayerController, KeyBindingsWidgetClass);

	// erase later
	KeyBindingsWidget->AddToViewport();
	KeyBindingsWidget->OpenKeyMapping();
}
