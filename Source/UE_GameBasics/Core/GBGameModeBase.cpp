// Fill out your copyright notice in the Description page of Project Settings.

#include "GBGameModeBase.h"
#include "GBCharacter.h"
#include "GBPlayerController.h"

AGBGameModeBase::AGBGameModeBase()
{
	DefaultPawnClass = AGBCharacter::StaticClass();;
	PlayerControllerClass = AGBPlayerController::StaticClass();
}

void AGBGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

void AGBGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGBGameModeBase::SaveGame()
{
}

void AGBGameModeBase::LoadGame()
{
}
