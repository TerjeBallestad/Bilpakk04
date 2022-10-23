// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BilpakkPawn.h"
#include "StateBase.h"
#include "Bilpakk04_Release/Bilpakk04_ReleaseGameModeBase.h"
#include "GameModeStateBase.generated.h"

/**
 * 
 */
UCLASS()
class BILPAKK04_RELEASE_API UGameModeStateBase : public UStateBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly)
	ABilpakk04_ReleaseGameModeBase* GameMode = nullptr;

	UPROPERTY(BlueprintReadOnly)
	ABilpakkPawn* Pawn = nullptr;

	
	
	virtual void OnEnterState(AActor* StateOwner) override;
	virtual void OnExitState() override;
	
};
