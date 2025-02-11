// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GBHUD.generated.h"

/**
 * 
 */
UCLASS()
class UE_GAMEBASICS_API AGBHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	AGBHUD();
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UUWPlayerKeyMapping> KeyBindingsWidgetClass;

	UPROPERTY(EditAnywhere)
	UUWPlayerKeyMapping* KeyBindingsWidget;
};
