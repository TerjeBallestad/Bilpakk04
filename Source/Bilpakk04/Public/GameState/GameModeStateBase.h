// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BilpakkPawn.h"
#include "StateMachine/StateBase.h"
#include "Bilpakk04/Bilpakk04GameModeBase.h"
#include "GameModeStateBase.generated.h"

/**
 * 
 */
UCLASS()
class BILPAKK04_API UGameModeStateBase : public UStateBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly)
	ABilpakk04GameModeBase* GameMode = nullptr;

	UPROPERTY(BlueprintReadOnly)
	AGameStateBilpakk* GameState = nullptr;

	UPROPERTY(BlueprintReadOnly)
	ABilpakkPawn* Pawn = nullptr;
	
	virtual void OnEnterState(AActor* StateOwner) override;
	virtual void OnExitState() override;

protected:
	virtual void PressPause();
	
};
