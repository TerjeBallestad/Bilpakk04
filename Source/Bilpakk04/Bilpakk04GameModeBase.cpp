// Copyright Epic Games, Inc. All Rights Reserved.


#include "Bilpakk04GameModeBase.h"

#include "Components/AudioComponent.h"
#include "GameState/GameStateBilpakk.h"

ABilpakk04GameModeBase::ABilpakk04GameModeBase()
{
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Component"));
	AudioComponent->SetupAttachment(GetRootComponent());
}

void ABilpakk04GameModeBase::BeginPlay()
{
	Super::BeginPlay();

	BindInput();
	BilpakkGameState = GetGameState<AGameStateBilpakk>();
}

void ABilpakk04GameModeBase::BindInput()
{
	InputComponent = NewObject<UInputComponent>(this);
	InputComponent->RegisterComponent();

	if (!InputComponent) return;
	InputComponent->BindAction("Pause", EInputEvent::IE_Pressed, this, &ABilpakk04GameModeBase::PauseGame);

	EnableInput(GetWorld()->GetFirstPlayerController());
}

void ABilpakk04GameModeBase::PauseGame()
{
	PauseDelegate.Broadcast();
}

FPauseSignature* ABilpakk04GameModeBase::GetPauseDelegate()
{
	return &PauseDelegate;
}
