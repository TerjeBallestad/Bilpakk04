// Fill out your copyright notice in the Description page of Project Settings.


#include "HandPackageStacker.h"

AHandPackageStacker::AHandPackageStacker()
{
	PrimaryActorTick.bCanEverTick = true;

	InteractionCollider = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionCollider"));
	InteractionCollider->SetupAttachment(MotionControllerComponent);
	InteractionCollider->InitSphereRadius(5);
	InteractionCollider->SetRelativeLocation(FVector(10, 0, 0));
	//MapWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Map"));
	//MapWidget->SetupAttachment(MotionControllerComponent);
	//MapWidget->SetVisibility(false);
}

void AHandPackageStacker::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &AHandPackageStacker::ActorBeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &AHandPackageStacker::ActorEndOverlap);
}

void AHandPackageStacker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PackageInGrip && GrippablePlayfield)
	{
		FTransform CurrentPreviewTransform;
		if (GrippablePlayfield->UpdatePreview(PackageInGrip, CurrentPreviewTransform))
		{
			PackageInGrip->MeshComponent->SetMaterial(0, PackageInGrip->HoloMaterial);
			if (!CurrentPreviewTransform.Equals(PreviousPreviewTransform))
			{
				AudioComponent->SetSound(GridTick);
				AudioComponent->Play();
			}
		}
		else
		{
			PackageInGrip->MeshComponent->SetMaterial(0, PackageInGrip->RedHoloMaterial);
			if (!CurrentPreviewTransform.Equals(PreviousPreviewTransform))
			{
				AudioComponent->SetSound(GridTickError);
				AudioComponent->Play();
			}
		}
		PreviousPreviewTransform = CurrentPreviewTransform;
	}
}

void AHandPackageStacker::GripPressed()
{
	SetGripState(EGripState::Grab);
	PackageInGrip = FindClosestPackageWithinRange();
	if (!PackageInGrip || PackageInGrip->bIsGripped)
	{
		PackageInGrip = nullptr;
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Triggering %s"), *PackageInGrip->GetName());
	PackageInGrip->StartInteract(this);
}

void AHandPackageStacker::GripReleased()
{
	SetGripState(EGripState::Open);

	if (!PackageInGrip) return;

	if (GrippablePlayfield)
	{
		if (!GrippablePlayfield->PlacePackage(PackageInGrip))
		{
			// Invalid placement inside playfield
			// PackageInGrip->PackageSpawner->SpawnQueue.Insert(PackageInGrip->PackageParameters, 0);
			PackageInGrip->Release();
		}
		else
		{

		}

	}
	else
	{
		// Invalid placement outside playfield
		// PackageInGrip->PackageSpawner->SpawnQueue.Insert(PackageInGrip->PackageParameters, 0);
		PackageInGrip->Release();
	}
	
	PackageInGrip->StopInteract();
	PackageInGrip = nullptr;
}

void AHandPackageStacker::SetGripState(EGripState NewState)
{
	GripState = NewState;
	GripStateChanged(NewState);
}

AStackablePackage* AHandPackageStacker::FindClosestPackageWithinRange()
{
	TArray<AActor*> Packages;
	InteractionCollider->GetOverlappingActors(Packages, AStackablePackage::StaticClass());
	float ShortestDistance = FLT_MAX;
	AStackablePackage* ClosestActor = nullptr;
	for (AActor* Package : Packages)
	{
		float Distance = FVector::Dist(InteractionCollider->GetComponentLocation(), Package->GetActorLocation());
		if (Distance < ShortestDistance)
		{
			ClosestActor = Cast<AStackablePackage>(Package);
			ShortestDistance = Distance;
		}
	}
	return ClosestActor;
}

// void AHandPackageStacker::SetMapEnabled(bool Enabled)
// {
// 	MapWidget->SetVisibility(Enabled);
// }
//
// void AHandPackageStacker::SetupMap()
// {
// 	MapWidget->SetVisibility(true);
// 	URouteMap* Map = Cast<URouteMap>(MapWidget->GetUserWidgetObject());
// 	if (Map)
// 	{
// 		Map->Setup();
// 	}
// }

void AHandPackageStacker::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (AStackablePackage* Package = Cast<AStackablePackage>(OtherActor))
	{
		if (!GrippablePackages.Contains(Package))
		{
			GripState = EGripState::CanGrab;
			GrippablePackages.Add(Package);
			//if(PackageInGrip == nullptr)
		}
	}
	if (APlayfieldContainer* PlayfieldContainer = Cast<APlayfieldContainer>(OtherActor))
	{
		GrippablePlayfield = PlayfieldContainer;
		if (PackageInGrip)
		{
			GrippablePlayfield->StartUpdatingPreview(PackageInGrip->PackageParameters.Material, PackageInGrip->MeshComponent->GetStaticMesh());
		}
	}
}

void AHandPackageStacker::ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (!GrippablePackages.Contains(OtherActor))
	{
		GrippablePackages.Remove(Cast<AStackablePackage>(OtherActor));

		if (GrippablePackages.Num() < 1 && PackageInGrip == nullptr)
		{
			GripState = EGripState::Open;
		}
	}

	if (OtherActor == GrippablePlayfield)
	{
		GrippablePlayfield->StopUpdatingPreview();
		GrippablePlayfield = nullptr;

		if (PackageInGrip)
		{
			PackageInGrip->MeshComponent->SetMaterial(0, PackageInGrip->PackageParameters.Material);
		}
	}
}



