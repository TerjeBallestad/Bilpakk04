// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "BilpakkVehicleFactoryNew.generated.h"

/**
 * 
 */
UCLASS()
class BILPAKK04EDITOR_API UBilpakkVehicleFactoryNew : public UFactory
{
	GENERATED_BODY()

public:
	UBilpakkVehicleFactoryNew(const FObjectInitializer& ObjectInitializer);

	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	virtual bool ShouldShowInNewMenu() const override;
	
};
