// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GBCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "GBPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UE_GAMEBASICS_API AGBPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AGBPlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
private:
	AGBCharacter* Character;

	void SetInputMappings();

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* IA_MoveForward;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* IA_MoveRight;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* IA_Jump;

	UPROPERTY(EditAnywhere, Category = "Input")
	float YawSensitivity = 0.8f;

	UPROPERTY(EditAnywhere, Category = "Input")
	float PitchSensitivity = 0.8f;
};
