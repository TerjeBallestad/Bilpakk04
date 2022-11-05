// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateMachine/StateManager.h"
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

	// Points
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	static int32 GetPoints(const UObject* WorldContextObject);

	UFUNCTION()
	void SetPoints(int32 Amount);

	UFUNCTION()
	void SetBonusPoints(int32 Amount);

	UFUNCTION()
	void AddBonusPoints(int32 Amount);

private:
	int32 Points;
	int32 BonusPoints;
};

