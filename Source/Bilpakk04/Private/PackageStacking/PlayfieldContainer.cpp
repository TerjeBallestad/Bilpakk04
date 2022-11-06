// Fill out your copyright notice in the Description page of Project Settings.


#include "PackageStacking/PlayfieldContainer.h"

#include "GameState/GameStateBilpakk.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

APlayfieldContainer::APlayfieldContainer()
{
	PrimaryActorTick.bCanEverTick = false;

	CarModel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Car"));
	SetRootComponent(CarModel);

	Grid = CreateDefaultSubobject<UPackageGrid>(TEXT("Grid"));
	PointsCalculator = CreateDefaultSubobject<UPackagePointsCalculator>(TEXT("Points Calculator"));
	StaticMeshPool = CreateDefaultSubobject<UActorPoolComponent>(TEXT("StaticMeshPool"));
	FloatingTextWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("FloatingTextWidget"));
	FloatingTextWidget->SetupAttachment(CarModel);
	NegativeFloatingTextWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("NegativeFloatingTextWidget"));
	NegativeFloatingTextWidget->SetupAttachment(CarModel);
}

void APlayfieldContainer::BeginPlay()
{
	Super::BeginPlay();

	PreviewActor = GetWorld()->SpawnActor<AActor>();
	PreviewMesh = NewObject<UStaticMeshComponent>(PreviewActor);
	if (PreviewMesh)
	{
		PreviewMesh->RegisterComponent();
		PreviewMesh->SetMobility(EComponentMobility::Movable);
		PreviewMesh->SetVisibility(false);
		PreviewActor->SetRootComponent(PreviewMesh);
	}
	GameState = Cast<AGameStateBilpakk>(UGameplayStatics::GetGameState(GetWorld()));
	
}


void APlayfieldContainer::Setup() const
{
	const FBilpakkLevelData Data = AGameStateBilpakk::GetLevelData(GetWorld());
	TArray<EPackageType> Colors;
	// TODO do we need row name?
	// LevelDataRowName = FName(Data.LevelName.ToString());
	FColorLibrary().Colors.GetKeys(Colors);
	Grid->Setup(Data.GridParameters, FTransform::Identity);
	PointsCalculator->Setup(Colors, Grid, Data.Doors);
}

bool APlayfieldContainer::PlacePackage(const AStackablePackage* ActivePackage)
{
	UStaticMeshComponent* NewPackage = StaticMeshPool->GetPooledActor();
	if (!NewPackage || !PreviewMesh->IsVisible()) return false;

	NewPackage->AttachToComponent(CarModel, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	NewPackage->SetStaticMesh(PreviewMesh->GetStaticMesh());
	NewPackage->SetMaterial(0, ActivePackage->PackageParameters.Material);
	NewPackage->SetWorldLocationAndRotation(PreviewActor->GetActorLocation(), PreviewActor->GetActorRotation());
	Grid->SetStatus(PreviewRange, ActivePackage->PackageParameters.Type);
	int32 Bonus = PointsCalculator->CalculatePlacePackagePoints(PreviewRange, ActivePackage->PackageParameters.Type);
	GameState->AddBonusPoints(Bonus);
	Points = PointsCalculator->CalculateEndGamePoints();
	Points.Diff += Bonus;
	Points.Bonus = Bonus;
	if (Points.Diff == abs(Points.Negative))
	{
		Points.Diff = 0;
		Points.Negative = 0;
	}
	// TODO
	GameState->SetPoints(Points.Total);
	FloatingTextWidget->SetWorldLocation(
		PreviewMesh->Bounds.Origin + FVector::UpVector * PreviewMesh->Bounds.BoxExtent.Z);
	NegativeFloatingTextWidget->SetWorldLocation(
		PreviewMesh->Bounds.Origin + FVector::UpVector * PreviewMesh->Bounds.BoxExtent.Z);

	// FRotator WidgetRotation = UKismetMathLibrary::FindLookAtRotation(FloatingTextWidget->GetComponentLocation(),GameState->StackingPawn->VRCamera->GetComponentLocation());
	// WidgetRotation.Pitch = 0;
	// FloatingTextWidget->SetWorldRotation(WidgetRotation);
	// NegativeFloatingTextWidget->SetWorldRotation(WidgetRotation);
	OnPointsAddedDelegate.Broadcast();
	ActivePackage->OnStackPackage();
	UE_LOG(LogTemp, Warning, TEXT("Returned Points: %d, and %d negative points, %d bonus, %d diff, %d from gamestate"), Points.Total, Points.Negative, Points.Bonus, Points.Diff, AGameStateBilpakk::GetPoints(GetWorld()));
	PreviewMesh->SetVisibility(false);
	return true;
	//TODO Disable collision
}

void APlayfieldContainer::StartUpdatingPreview(UMaterialInstance* Material, UStaticMesh* Mesh)
{
	PreviewMesh->SetVisibility(true);
	PreviewMesh->SetMaterial(0, Material);
	PreviewMesh->SetStaticMesh(Mesh);
	PreviewMesh->SetVisibility(true);
	bUpdatePreview = true;
}

void APlayfieldContainer::StopUpdatingPreview()
{
	PreviewMesh->SetVisibility(false);
	bUpdatePreview = false;
}

bool APlayfieldContainer::UpdatePreview(const AStackablePackage* ActivePackage, FTransform& InOutPreviewTransform)
{
	FVector Min;
	FVector Max;
	PreviewMesh->GetLocalBounds(Min, Max);
	Grid->CalculatePackageBounds(ActivePackage->GetTransform(), Min, Max, PreviewRange);
	if (Grid->FindSpaceForPackage(ActivePackage->GetTransform(), PreviewRange, InOutPreviewTransform))
	{
		if (PreviewMovementThreshold < FVector::Distance(PreviewActor->GetActorLocation(),
		                                                 InOutPreviewTransform.GetLocation()))
		{
			PreviewActor->SetActorTransform(InOutPreviewTransform);
		}
		PreviewMesh->SetVisibility(true);
		return true;
	}
	PreviewMesh->SetVisibility(false);
	return false;
}
