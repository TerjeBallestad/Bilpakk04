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
	MeshComponent->SetMaterial(0, NewPackage.Material);
	MeshComponent->SetStaticMesh(NewPackage.Mesh);
}

void AStackablePackage::OnReleased() 
{
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	bIsGripped = false;
	UE_LOG(LogTemp, Warning, TEXT("Released delegate is bound %s"), PackageReleasedDelegate.IsBound() ? TEXT("True") : TEXT("False"));
	UE_LOG(LogTemp, Warning, TEXT("Package stacked delegate is bound %s"), PackageStackedDelegate.IsBound() ? TEXT("True") : TEXT("False"));
	
	PackageReleasedDelegate.Broadcast();
	PackageStackedDelegate.Clear();
	PackageReleasedDelegate.Clear();
}

void AStackablePackage::StartInteract(AHandController* HandController)
{
	if (bIsGripped) return;

	AttachToActor(HandController, FAttachmentTransformRules::KeepWorldTransform);
	bIsGripped = true;
	UE_LOG(LogTemp, Warning, TEXT("Being gripped by %s "), *HandController->GetName());
}

FPackagePlacedSignature* AStackablePackage::GetPackageStackedDelegate()
{
	return &PackageStackedDelegate;
}

FPackagePlacedSignature* AStackablePackage::GetPackageReleasedDelegate()
{
	return &PackageReleasedDelegate;
}
