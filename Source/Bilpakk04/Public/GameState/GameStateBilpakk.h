// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameStateInterface.h"
#include "StateManager.h"
#include "GameFramework/GameStateBase.h"
#include "GameStateBilpakk.generated.h"

/**
 * 
 */
UCLASS()
class BILPAKK04_API AGameStateBilpakk : public AGameStateBase
{
	GENERATED_BODY()


public:
	AGameStateBilpakk();
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UStateManager* StateManager;
};

