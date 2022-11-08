// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorPoolComponent.h"
#include "Data/BilpakkLevelData.h"
#include "PackageGrid.h"
#include "Components/ActorComponent.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"
#include "PackagePointsCalculator.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BILPAKK04_API UPackagePointsCalculator : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPackagePointsCalculator();

	virtual void BeginPlay() override;
	void Setup(TArray<EPackageType> Colors, UPackageGrid* Grid, TArray<FGridRange> InDoors);
	void SpawnNegativeIndicator(FGridRange Package);

	UFUNCTION(BlueprintCallable)
	FPoints CalculateEndGamePoints();

	UFUNCTION(BlueprintCallable)
	int32 CalculatePlacePackagePoints(FGridRange Range, EPackageType Color);

	UPROPERTY(EditDefaultsOnly)
	USoundCue* ErrorSound;

	UPROPERTY(EditDefaultsOnly)
	USoundCue* GoodPlacement;

	UPROPERTY(EditDefaultsOnly)
	USoundCue* FinalPlacement;

private:
	void DrawDebugRange(FIntVector Range);

	UPROPERTY()
	UActorPoolComponent* MeshPool;

	UFUNCTION()
	void SetMeshPoolInvisible();
	int32 CalculatePackagePoints(FIntVector PackageSize);

	UPROPERTY()
	int32 PreviousPoints = 0;

	UPROPERTY()
	UAudioComponent* AudioComponent;

	UPROPERTY()
	UPackageGrid* PackageGrid;

	UPROPERTY()
	TArray<FGridRange> Doors;
	
	UPROPERTY(VisibleAnywhere)
	TMap<EPackageType, FPackageChunks> PackageClusters;

	UPROPERTY()
	TArray<FGridRange> PositivePackages;

	UPROPERTY()
	TArray<FGridRange> NegativePackages;

	UPROPERTY(EditDefaultsOnly)
	UMaterial* NegativeMaterial;

	UPROPERTY(EditDefaultsOnly)
	UMaterial* PositiveMaterial;

	UPROPERTY(EditDefaultsOnly)
	UStaticMesh* CubeMesh;
	


		
};
