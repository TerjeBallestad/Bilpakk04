// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HandUI.h"
#include "HandPackageStacker.h"
#include "GameFramework/Actor.h"
#include "UObject/NoExportTypes.h"
#include "ControllerMode.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class BILPAKK04_RELEASE_API UControllerMode : public UObject
{
	GENERATED_BODY()

public:
	UControllerMode();

	void BindHands(USceneComponent* Root);

	virtual void SetHandsHiddenInGame(bool bNewHidden);

	void GripLeft() { LeftHandController->GripPressed(); }
	void TriggerLeft() { LeftHandController->TriggerPressed(); }
	void GripReleaseLeft() { LeftHandController->GripReleased(); }
	void TriggerReleaseLeft() { LeftHandController->TriggerReleased(); }

	void GripRight() { RightHandController->GripPressed(); }
	void TriggerRight() { RightHandController->TriggerPressed(); }
	void GripReleaseRight() { RightHandController->GripReleased(); }
	void TriggerReleaseRight() { RightHandController->TriggerReleased(); }

	UPROPERTY(VisibleAnywhere)
	AHandController* RightHandController;

	UPROPERTY(VisibleAnywhere)
	AHandController* LeftHandController;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AHandController> HandControllerClass;

private:
	UPROPERTY()
	bool bHandsBound = false;
	
};
