// Fill out your copyright notice in the Description page of Project Settings.


#include "ControllerMode.h"


UControllerMode::UControllerMode(){}

void UControllerMode::BindHands(USceneComponent* Root)
{
	if (bHandsBound) return;

	RightHandController = GetWorld()->SpawnActor<AHandController>(HandControllerClass);
	LeftHandController = GetWorld()->SpawnActor<AHandController>(HandControllerClass);

	if (RightHandController)
	{
		RightHandController->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
		RightHandController->SetOwner(Root->GetOwner());
		RightHandController->SetHand(EControllerHand::Right);
	}
	if (LeftHandController)
	{
		LeftHandController->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
		LeftHandController->SetOwner(Root->GetOwner());
		LeftHandController->SetHand(EControllerHand::Left);
	}

	bHandsBound = true;
}

void UControllerMode::SetHandsHiddenInGame(bool bNewHidden)
{
	LeftHandController->SetActorHiddenInGame(bNewHidden);
	RightHandController->SetActorHiddenInGame(bNewHidden);

	if (AHandPackageStacker* HandController = Cast<AHandPackageStacker>(LeftHandController))
	{
		HandController->SetGripState(EGripState::Open);
	}
	if (AHandPackageStacker* HandController = Cast<AHandPackageStacker>(RightHandController))
	{
		HandController->SetGripState(EGripState::Open);
	}

	// TODO return package in grip
}
