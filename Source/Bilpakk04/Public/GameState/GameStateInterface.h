// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameStateInterface.generated.h"

DECLARE_MULTICAST_DELEGATE(FPauseSignature)

UINTERFACE(MinimalAPI)
class UGameStateInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BILPAKK04_API IGameStateInterface
{
	GENERATED_BODY()

public:
	virtual FPauseSignature* GetPauseDelegate() = 0;
};
