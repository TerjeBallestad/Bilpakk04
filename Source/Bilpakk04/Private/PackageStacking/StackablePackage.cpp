// Fill out your copyright notice in the Description page of Project Settings.


#include "PackageStacking/StackablePackage.h"

AStackablePackage::AStackablePackage()
{
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(MeshComponent);
}

void AStackablePackage::Setup(FPackageParameters NewPackage)
{
	PackageParameters = NewPackage;

	MeshComponent->SetStaticMesh(NewPackage.Mesh);
}

void AStackablePackage::StartInteract(AHandController* HandController)
{
	if (bIsGripped) return;

	AttachToActor(HandController, FAttachmentTransformRules::KeepWorldTransform);
	bIsGripped = true;
	UE_LOG(LogTemp, Warning, TEXT("Being gripped by %s "), *HandController->GetName());
}

void AStackablePackage::StopInteract()
{
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	bIsGripped = false;
	Release();
}
