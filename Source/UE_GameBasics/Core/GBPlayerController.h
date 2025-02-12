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
	void SetInputMappings();

	void MoveForward(const FInputActionValue& Value);
	void MoveRight(const FInputActionValue& Value);
	void Jump(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Zoom(const FInputActionValue& Value);
	void ToggleWalkRun(const FInputActionValue& Value);
	void ToggleCrouch(const FInputActionValue& Value);


	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* MappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* IA_MoveForward;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* IA_MoveRight;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* IA_Jump;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* IA_Look;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* IA_Zoom;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* IA_ToggleWalkRun;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* IA_ToggleCrouch;

	UPROPERTY(EditAnywhere, Category = "Input")
	float YawSensitivity = 0.8f;

	UPROPERTY(EditAnywhere, Category = "Input")
	float PitchSensitivity = 0.8f;

public:
	UInputMappingContext* GetMappingContext() const { return MappingContext; };

	UFUNCTION()
	void RebindActionKey(const FName Action, const FKey FormerKey, const FKey NewKey);


};
