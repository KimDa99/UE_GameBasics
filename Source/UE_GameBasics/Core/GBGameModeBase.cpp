// Fill out your copyright notice in the Description page of Project Settings.

#include "GBGameModeBase.h"
#include "GBCharacter.h"
#include "HUD/GBHUD.h"
#include "GBPlayerController.h"

AGBGameModeBase::AGBGameModeBase()
{
	DefaultPawnClass = AGBCharacter::StaticClass();;
	PlayerControllerClass = AGBPlayerController::StaticClass();
	HUDClass = AGBHUD::StaticClass();
}


void AGBGameModeBase::SaveGame()
{
}

void AGBGameModeBase::LoadGame()
{
}
