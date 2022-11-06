// Fill out your copyright notice in the Description page of Project Settings.


#include "GameState/NewGameStackingState.h"

#include "PackageStacking/PackageSpawner.h"

void UNewGameStackingState::OnEnterState(AActor* StateOwner)
{
	Super::OnEnterState(StateOwner);

	GameState->SetPoints(0);
	GameState->SetBonusPoints(0);

	FName Row(GameState->RowName);
	const UDataTable *LevelDataTable = GameState->LevelDataTable;

	if(!LevelDataTable)
	{
		UE_LOG(LogTemp, Warning, TEXT("No data table in Game State"))
		return;
	};
	
	if(Row == "")
	{
		UE_LOG(LogTemp, Warning, TEXT("No Row Name in Start Game"))
		Row = LevelDataTable->GetRowNames()[0];
	}
	UE_LOG(LogTemp, Warning, TEXT("Starting row: %s"), *Row.ToString());
	
	GameState->LevelData = *LevelDataTable->FindRow<FBilpakkLevelData>(Row, "");
	GameState->RowName = Row.ToString();
	
	if (GameMusic)
	{
		GameMode->AudioComponent->SetSound(GameMusic);
		GameMode->AudioComponent->Play();
	}

	GameState->PackageSpawner->Setup();
	GameState->PlayfieldContainer->Setup();
	// delay here
	GameState->PackageSpawner->SpawnNextPackage();
	GameState->StateManager->SwitchStateByKey("stacking");
}

void UNewGameStackingState::OnExitState()
{
	Super::OnExitState();
}
