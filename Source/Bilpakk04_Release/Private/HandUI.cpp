// Fill out your copyright notice in the Description page of Project Settings.


#include "HandUI.h"

AHandUI::AHandUI()
{
	WidgetPointer = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("Pointer"));
	WidgetPointer->SetupAttachment(GetRootComponent());
}

void AHandUI::TriggerPressed()
{
	WidgetPointer->PressPointerKey(EKeys::LeftMouseButton);

}

void AHandUI::TriggerReleased()
{
	WidgetPointer->ReleasePointerKey(EKeys::LeftMouseButton);
}
