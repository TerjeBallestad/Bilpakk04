// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "StateManager.h"
#include "GameFramework/GameModeBase.h"
#include "Bilpakk04_ReleaseGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class BILPAKK04_RELEASE_API ABilpakk04_ReleaseGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABilpakk04_ReleaseGameModeBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStateManager* StateManager;
};
