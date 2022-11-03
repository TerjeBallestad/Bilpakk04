// Fill out your copyright notice in the Description page of Project Settings.


#include "GameState/NewGameStackingState.h"

void UNewGameStackingState::OnEnterState(AActor* StateOwner)
{
	Super::OnEnterState(StateOwner);

	GameState->SetPoints(0);
	GameState->SetBonusPoints(0);

	// Load level data
	if (GameMusic)
	{
		GameMode->AudioComponent->SetSound(GameMusic);
		GameMode->AudioComponent->Play();
	}
	GameState->StateManager->SwitchStateByKey("stacking");
}

void UNewGameStackingState::OnExitState()
{
	Super::OnExitState();
}
