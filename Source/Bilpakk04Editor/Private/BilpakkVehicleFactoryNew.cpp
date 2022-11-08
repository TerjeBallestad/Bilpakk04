// Fill out your copyright notice in the Description page of Project Settings.


#include "BilpakkVehicleFactoryNew.h"

#include "Data/BilpakkVehicleData.h"

UBilpakkVehicleFactoryNew::UBilpakkVehicleFactoryNew(const FObjectInitializer& ObjectInitializer)
{
	SupportedClass = UBilpakkVehicleData::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}

UObject* UBilpakkVehicleFactoryNew::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName,
                                                     EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	 return NewObject<UBilpakkVehicleData>(InParent, InClass, InName, Flags);
	
}

bool UBilpakkVehicleFactoryNew::ShouldShowInNewMenu() const
{
	return true;
}
