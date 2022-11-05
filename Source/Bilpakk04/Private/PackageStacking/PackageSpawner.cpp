// Fill out your copyright notice in the Description page of Project Settings.


#include "PackageStacking/PackageSpawner.h"

#include "GameState/GameStateBilpakk.h"

APackageSpawner::APackageSpawner()
{
	PrimaryActorTick.bCanEverTick = false;

	PackagePool = CreateDefaultSubobject<UGenericActorPoolComponent>(TEXT("PackagePool"));
}

void APackageSpawner::BeginPlay()
{
	Super::BeginPlay();
}

void APackageSpawner::Setup()
{
	FBilpakkLevelData Data = AGameStateBilpakk::GetLevelData(GetWorld());

	SpawnQueue.Empty();

	TArray<EPackageType> Colors;
	ColorLibrary.Colors.GetKeys(Colors);

	if (Materials.Num() < 1)
	{
		for (EPackageType Color : Colors)
		{
			UMaterialInstanceDynamic* Material = UMaterialInstanceDynamic::Create(MaterialClass, this);
			Material->SetVectorParameterValue("Color", ColorLibrary.Colors[Color]);
			Materials.Add(Color, Material);
		}
	}

	PackageLibrary = Data.PackageLibrary;
	TArray<EPackageType> PackageTypes;
	Data.PackageAmounts.GenerateKeyArray(PackageTypes);
	for (const EPackageType Pt : PackageTypes)
	{
		TArray<EPackageSize> Sizes;
		Data.PackageAmounts[Pt].Amounts.GetKeys(Sizes);
		for (const EPackageSize Size : Sizes)
		{
			for (int i = 0; i < Data.PackageAmounts[Pt].Amounts[Size]; ++i)
			{
				FPackageParameters Package;
				Package.Material = Materials[Pt];
				Package.Mesh = PackageLibrary[Size].Mesh;
				Package.SizeInt = PackageLibrary[Size].SizeInt;
				Package.Type = Pt;
				Package.SizeE = Size;
				SpawnQueue.Add(Package);
			}
		}
	}
	ShuffleArray(SpawnQueue);
}

int32 APackageSpawner::GetRemainingPackageAmount(UObject* WorldContextObject)
{
	return 32;
}

AStackablePackage* APackageSpawner::GetNextPackage()
{
	if (SpawnQueue.Num() < 1)
	{
		// FTimerHandle Handle;
		// GetWorldTimerManager().SetTimer(Handle, GameState, &ABilpakkGameState::FinishGame, 2, false);
		return nullptr;
	}
	FTransform SpawnLocation = GetActorTransform() + PackageSpawnLocation;
	SpawnLocation.SetRotation(GetActorRotation().Quaternion());	
	const FActorSpawnParameters PackageSpawnParameters;

	AStackablePackage* Package = Cast<AStackablePackage>(PackagePool->Spawn(PackageClass, SpawnLocation, PackageSpawnParameters));
	Package->Setup(SpawnQueue[0]);
	Package->GetPlacePackageDelegate()->AddUObject(this, &APackageSpawner::RemoveFirstPackageFromQueue);

	return Package;
}

void APackageSpawner::RemoveFirstPackageFromQueue()
{
	if(SpawnQueue.Num() > 0)
	{
		SpawnQueue.RemoveAt(0);
	}
}

void APackageSpawner::ShuffleArray(TArray<FPackageParameters>& Array)
{
	if (Array.Num() > 0)
	{
		int32 LastIndex = Array.Num() - 1;
		for (int32 i = 0; i <= LastIndex; ++i)
		{
			int32 Index = FMath::RandRange(i, LastIndex);
			if (i != Index)
			{
				Array.Swap(i, Index);
			}
		}
	}
}
