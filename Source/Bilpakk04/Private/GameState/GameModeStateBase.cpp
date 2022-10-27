// Fill out your copyright notice in the Description page of Project Settings.


#include "GameState/GameModeStateBase.h"

#include "Kismet/GameplayStatics.h"

void UGameModeStateBase::OnEnterState(AActor* StateOwner)
{
	Super::OnEnterState(StateOwner);

	if (!GameMode)
	{
		GameMode = Cast<ABilpakk04GameModeBase>(StateOwner);
	}
	if (!Pawn)
	{
		Pawn = Cast<ABilpakkPawn>(UGameplayStatics::GetPlayerController(this, 0)->GetPawn());
	}
}

void UGameModeStateBase::OnExitState()
{
	Super::OnExitState();
}
