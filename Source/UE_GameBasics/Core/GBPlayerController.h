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
	const FString IMCPath = "/Game/Core/Controllers/IMC_Player.IMC_Player";
	const FString IA_MoveForwardPath = "/Game/Core/Controllers/IA_MoveForward.IA_MoveForward";
	const FString IA_MoveRightPath = "/Game/Core/Controllers/IA_MoveRight.IA_MoveRight";
	const FString IA_JumpPath = "/Game/Core/Controllers/IA_Jump.IA_Jump";
	const FString IA_LookPath = "/Game/Core/Controllers/IA_Look.IA_Look";
	const FString IA_ZoomPath = "/Game/Core/Controllers/IA_Zoom.IA_Zoom";
	const FString IA_ToggleWalkRunPath = "/Game/Core/Controllers/IA_ToggleWalkRun.IA_ToggleWalkRun";
	const FString IA_ToggleCrouchPath = "/Game/Core/Controllers/IA_ToggleCrouch.IA_ToggleCrouch";

private:
	void SetInputMappings();
	template<typename T>
	T* LoadObject(const FString& Path);

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
