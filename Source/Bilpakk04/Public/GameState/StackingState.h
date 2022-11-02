// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameState/GameModeStateBase.h"
#include "StackingState.generated.h"

/**
 * 
 */
UCLASS()
class BILPAKK04_API UStackingState : public UGameModeStateBase
{
	GENERATED_BODY()

	virtual void OnEnterState(AActor* StateOwner) override;
	virtual void OnExitState() override;

protected:
	virtual void PressPause() override;
};
