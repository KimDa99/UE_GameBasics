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

public:
	// Sets default values for this character's properties
	AGBCharacter();

private:
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComponent;

	FRotator BaseMeshRotation = FRotator(0.0f, -90.0f, 0.0f);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ToggleWalkRun();
	void ToggleCrouch();
	bool IsCrouching;
public:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Look(FVector2D Value);
	void Zoom(float Value);

	void ZoomCamera(float Value);
};
