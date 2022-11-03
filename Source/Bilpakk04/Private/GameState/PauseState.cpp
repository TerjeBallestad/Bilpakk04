// Fill out your copyright notice in the Description page of Project Settings.


#include "GameState/PauseState.h"

void UPauseState::OnEnterState(AActor* StateOwner)
{
	Super::OnEnterState(StateOwner);
	
	Pawn->SetControllerModeUI();
}

void UPauseState::OnExitState()
{
	Super::OnExitState();
}

void UPauseState::PressPause()
{
	GameState->StateManager->SwitchStateByKey("stacking");
}
