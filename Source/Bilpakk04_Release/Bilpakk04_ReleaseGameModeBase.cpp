// Copyright Epic Games, Inc. All Rights Reserved.


#include "Bilpakk04_ReleaseGameModeBase.h"

ABilpakk04_ReleaseGameModeBase::ABilpakk04_ReleaseGameModeBase()
{
	StateManager = CreateDefaultSubobject<UStateManager>(TEXT("Game State Manager"));
}
