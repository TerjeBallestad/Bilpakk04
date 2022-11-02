// Fill out your copyright notice in the Description page of Project Settings.


#include "GameState/GameModeStateBase.h"

#include "Kismet/GameplayStatics.h"

void UGameModeStateBase::OnEnterState(AActor* StateOwner)
{
	Super::OnEnterState(StateOwner);

	if (!GameState)
	{
		GameState = Cast<AGameStateBilpakk>(StateOwner);
	}
	if (!GameMode)
	{
		GameMode = Cast<ABilpakk04GameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	}
	if (GameMode)
	{
		GameMode->GetPauseDelegate()->AddUObject(this, &UGameModeStateBase::PressPause);
	}
}

void UGameModeStateBase::OnExitState()
{
	Super::OnExitState();
	GameMode->GetPauseDelegate()->RemoveAll(this);
}

void UGameModeStateBase::PressPause()
{
}
