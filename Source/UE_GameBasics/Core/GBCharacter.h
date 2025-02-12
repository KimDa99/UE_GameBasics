// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EngineMinimal.h"
#include "GameFramework/Character.h"
#include "GBCharacter.generated.h"

UCLASS()
class UE_GAMEBASICS_API AGBCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComponent;

	FRotator BaseMeshRotation = FRotator(0.0f, -90.0f, 0.0f);

	const FString MeshPath = "/Game/Characters/Mannequins/Meshes/SKM_Quinn.SKM_Quinn";
	const FString AnimBPPath = "/Game/Characters/Mannequins/Animations/ABP_Quinn.ABP_Quinn_C";


public:
	AGBCharacter();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

public:
	void ToggleWalkRun();
	void ToggleCrouch();
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Look(FVector2D Value);
	void Zoom(float Value);
	void ZoomCamera(float Value);

private:
	bool IsCrouching;
	
	void SetupSpringArm();
	void SetupCamera();
	void SetupMesh();
	void SetupCharacterMovement();

};
