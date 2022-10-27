// Fill out your copyright notice in the Description page of Project Settings.


#include "HandController.h"

// Sets default values
AHandController::AHandController()
{
	PrimaryActorTick.bCanEverTick = true;

	MotionControllerComponent = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionController"));
	SetRootComponent(MotionControllerComponent);

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComponent->SetupAttachment(MotionControllerComponent);

}