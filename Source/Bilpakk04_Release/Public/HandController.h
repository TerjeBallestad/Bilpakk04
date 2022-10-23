// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MotionControllerComponent.h"
#include "Components/AudioComponent.h"
#include "HandController.generated.h"

UCLASS()
class BILPAKK04_RELEASE_API AHandController : public AActor
{
	GENERATED_BODY()

public:
	AHandController();

	virtual void SetHand(const EControllerHand Hand) const { MotionControllerComponent->SetTrackingSource(Hand); };
	virtual void GripPressed() {};
	virtual void GripReleased() {};
	virtual void TriggerPressed() {};
	virtual void TriggerReleased() {};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UMotionControllerComponent* MotionControllerComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAudioComponent* AudioComponent;
};
