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
