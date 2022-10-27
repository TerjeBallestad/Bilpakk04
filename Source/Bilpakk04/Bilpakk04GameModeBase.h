// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "StateManager.h"
#include "GameFramework/GameModeBase.h"
#include "Bilpakk04GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class BILPAKK04_API ABilpakk04GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABilpakk04GameModeBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStateManager* StateManager;
};
