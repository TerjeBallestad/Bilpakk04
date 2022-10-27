// Copyright Epic Games, Inc. All Rights Reserved.


#include "Bilpakk04GameModeBase.h"

ABilpakk04GameModeBase::ABilpakk04GameModeBase()
{
	StateManager = CreateDefaultSubobject<UStateManager>(TEXT("Game State Manager"));
}
