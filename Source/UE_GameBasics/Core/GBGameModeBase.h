// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GBGameModeBase.generated.h"

/**
 * Role: GameModeBase
 *	- The GameModeBase class is the base class for all game modes.
 *	- A game mode defines the game being played, including rules, scoring, and other aspects.
 *	- The game mode exists only on the server and is responsible for handling gameplay logic.
 */

UCLASS()
class UE_GAMEBASICS_API AGBGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	// Constructor
	AGBGameModeBase();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// Save the game
	UFUNCTION(BlueprintCallable, Category = "Game")
	void SaveGame();

	// Load the game
	UFUNCTION(BlueprintCallable, Category = "Game")	
	void LoadGame();	
};
