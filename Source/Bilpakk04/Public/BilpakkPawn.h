// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "HandController.h"
#include "GameFramework/Pawn.h"
#include "ControllerMode.h"
#include "StateMachine/StateManager.h"
#include "BilpakkPawn.generated.h"


UCLASS()
class BILPAKK04_API ABilpakkPawn : public APawn
{
	GENERATED_BODY()

public:
	ABilpakkPawn();

protected:
	virtual void BeginPlay() override;

	void SetupHands();

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintReadOnly)
	UCameraComponent* VRCamera;

	UFUNCTION(BlueprintCallable)
	void SetControllerModeUI();

	UFUNCTION(BlueprintCallable)
	void SetControllerModePackageStacker();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStateManager* StateManager;

private:
	void GripLeft() { CurrentControllerMode->GripLeft(); }
	void TriggerLeft() { CurrentControllerMode->TriggerLeft(); }
	void GripReleaseLeft() { CurrentControllerMode->GripReleaseLeft(); }
	void TriggerReleaseLeft() { CurrentControllerMode->TriggerReleaseLeft(); }

	void GripRight() { CurrentControllerMode->GripRight(); }
	void TriggerRight() { CurrentControllerMode->TriggerRight(); }
	void GripReleaseRight() { CurrentControllerMode->GripReleaseRight(); }
	void TriggerReleaseRight() { CurrentControllerMode->TriggerReleaseRight(); }

	UPROPERTY(VisibleAnywhere)
	UControllerMode* ControllerModeUI;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UControllerMode> ControllerModeUIClass;

	UPROPERTY(VisibleAnywhere)
	UControllerMode* ControllerModePackageStacker;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UControllerMode> ControllerModePackageStackerClass;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* VRRoot;

	UPROPERTY(VisibleAnywhere)
	UControllerMode* CurrentControllerMode;
};
