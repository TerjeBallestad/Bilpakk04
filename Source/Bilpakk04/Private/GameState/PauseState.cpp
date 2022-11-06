// Fill out your copyright notice in the Description page of Project Settings.


#include "GameState/PauseState.h"

#include "PackageStacking/PackageSpawner.h"

void UPauseState::OnEnterState(AActor* StateOwner)
{
	Super::OnEnterState(StateOwner);
	GameState->PackageSpawner->SetActorHiddenInGame(true);
	GameState->PlayfieldContainer->SetActorHiddenInGame(true);
	Pawn->SetControllerModeUI();
}

void UPauseState::OnExitState()
{
	Super::OnExitState();
	GameState->PackageSpawner->SetActorHiddenInGame(false);
	GameState->PlayfieldContainer->SetActorHiddenInGame(false);
}

void UPauseState::PressPause()
{
	GameState->StateManager->SwitchStateByKey("stacking");
}
