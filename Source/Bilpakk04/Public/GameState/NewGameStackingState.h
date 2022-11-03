// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameState/GameModeStateBase.h"
#include "NewGameStackingState.generated.h"

/**
 * 
 */
UCLASS()
class BILPAKK04_API UNewGameStackingState : public UGameModeStateBase
{
	GENERATED_BODY()

	virtual void OnEnterState(AActor* StateOwner) override;
	virtual void OnExitState() override;
	
};
