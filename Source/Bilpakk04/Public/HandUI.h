// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HandController.h"
#include "Components/WidgetInteractionComponent.h"
#include "HandUI.generated.h"

/**
 * 
 */
UCLASS()
class BILPAKK04_API AHandUI : public AHandController
{
	GENERATED_BODY()

public:
	AHandUI();

	virtual void TriggerPressed() override;
	virtual void TriggerReleased() override;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UWidgetInteractionComponent* WidgetPointer;
};
