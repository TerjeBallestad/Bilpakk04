// Fill out your copyright notice in the Description page of Project Settings.


#include "BilpakkPawn.h"
#include "Kismet/GameplayStatics.h"

ABilpakkPawn::ABilpakkPawn()
{
	PrimaryActorTick.bCanEverTick = false;

	VRRoot = CreateDefaultSubobject<USceneComponent>(TEXT("VRRoot"));
	SetRootComponent(VRRoot);

	VRCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("VRCamera"));
	VRCamera->SetupAttachment(VRRoot);

	StateManager = CreateDefaultSubobject<UStateManager>(TEXT("Player State Manager"));
}

void ABilpakkPawn::BeginPlay()
{
	Super::BeginPlay();

	SetupHands();
	
}

void ABilpakkPawn::SetupHands()
{
	ControllerModeUI = NewObject<UControllerMode>(this, ControllerModeUIClass, FName("ControllerModeUI"));
	ControllerModePackageStacker = NewObject<UControllerMode>(this, ControllerModePackageStackerClass, FName("ControllerModePackageStacker"));
	CurrentControllerMode = ControllerModePackageStacker;
	ControllerModeUI->BindHands(VRRoot);
	ControllerModePackageStacker->BindHands(VRRoot);
	ControllerModeUI->SetHandsHiddenInGame(true);
}

void ABilpakkPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);
	if (PlayerInputComponent)
	{
		/*PlayerInputComponent->BindAxis(TEXT("LeftVertical"), this, &AVRCarpakPawn::UpdateVertical);
		PlayerInputComponent->BindAxis(TEXT("LeftHorizontal"), this, &AVRCarpakPawn::UpdateHorizontal);*/
		PlayerInputComponent->BindAction(TEXT("RightGrip"), IE_Pressed, this, &ABilpakkPawn::GripRight);
		PlayerInputComponent->BindAction(TEXT("RightGrip"), IE_Released, this, &ABilpakkPawn::GripReleaseRight);
		PlayerInputComponent->BindAction(TEXT("LeftGrip"), IE_Pressed, this, &ABilpakkPawn::GripLeft);
		PlayerInputComponent->BindAction(TEXT("LeftGrip"), IE_Released, this, &ABilpakkPawn::GripReleaseLeft);
		PlayerInputComponent->BindAction(TEXT("LeftTrigger"), IE_Pressed, this, &ABilpakkPawn::TriggerLeft);
		PlayerInputComponent->BindAction(TEXT("LeftTrigger"), IE_Released, this, &ABilpakkPawn::TriggerReleaseLeft);
		PlayerInputComponent->BindAction(TEXT("RightTrigger"), IE_Pressed, this, &ABilpakkPawn::TriggerRight);
		PlayerInputComponent->BindAction(TEXT("RightTrigger"), IE_Released, this, &ABilpakkPawn::TriggerReleaseRight);
	}

}

void ABilpakkPawn::SetControllerModeUI()
{
	CurrentControllerMode->SetHandsHiddenInGame(true);
	ControllerModeUI->SetHandsHiddenInGame(false);
	CurrentControllerMode = ControllerModeUI;
}

void ABilpakkPawn::SetControllerModePackageStacker()
{
	CurrentControllerMode->SetHandsHiddenInGame(true);
	ControllerModePackageStacker->SetHandsHiddenInGame(false);
	CurrentControllerMode = ControllerModePackageStacker;
}

