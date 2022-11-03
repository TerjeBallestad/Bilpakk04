// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "StateManager.h"
#include "GameFramework/GameModeBase.h"
#include "GameState/GameStateBilpakk.h"
#include "GameState/GameStateInterface.h"
#include "Bilpakk04GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class BILPAKK04_API ABilpakk04GameModeBase : public AGameModeBase, public IGameStateInterface
{
	GENERATED_BODY()

public:
	ABilpakk04GameModeBase();

	virtual void BeginPlay() override;
	void BindInput();
	void PauseGame();
	virtual FPauseSignature* GetPauseDelegate() override;

	UPROPERTY(BlueprintReadOnly)
	UAudioComponent* AudioComponent;

protected:

	UPROPERTY()
	AGameStateBilpakk* BilpakkGameState;

private:
	FPauseSignature PauseDelegate;
};

