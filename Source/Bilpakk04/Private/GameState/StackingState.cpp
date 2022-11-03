// Fill out your copyright notice in the Description page of Project Settings.


#include "GameState/StackingState.h"

void UStackingState::OnEnterState(AActor* StateOwner)
{
	Super::OnEnterState(StateOwner);
	
	Pawn->SetControllerModePackageStacker();
	GameMode->AudioComponent->SetPaused(false);
}

void UStackingState::OnExitState()
{
	Super::OnExitState();
	GameMode->AudioComponent->SetPaused(true);
}

void UStackingState::PressPause()
{
	GameState->StateManager->SwitchStateByKey("pause");
}
