// Fill out your copyright notice in the Description page of Project Settings.


#include "GameState/GameStateBilpakk.h"

AGameStateBilpakk::AGameStateBilpakk()
{
	StateManager = CreateDefaultSubobject<UStateManager>(TEXT("Game State Manager"));
}

void AGameStateBilpakk::BeginPlay()
{
	Super::BeginPlay();
	StateManager->InitStateManager();
}

int32 AGameStateBilpakk::GetPoints(const UObject* WorldContextObject)
{
	if((!GEngine) && (!WorldContextObject)) return -1;

	const AGameStateBilpakk* State = Cast<AGameStateBilpakk>(GEngine->
	GetWorldFromContextObjectChecked(WorldContextObject)->
	GetAuthGameMode()->GameState);
	
	if(State) return State->Points;
	
	return -1;
}

void AGameStateBilpakk::SetPoints(const int32 Amount)
{
	Points = Amount + BonusPoints;
}

void AGameStateBilpakk::SetBonusPoints(const int32 Amount)
{
	BonusPoints = Amount;
}

void AGameStateBilpakk::AddBonusPoints(const int32 Amount)
{
	BonusPoints += Amount;
}
