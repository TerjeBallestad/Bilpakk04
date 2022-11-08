// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/BilpakkLevelData.h"
#include "Components/ActorComponent.h"
#include "PackageGrid.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BILPAKK04_API UPackageGrid : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPackageGrid();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	TMap<FIntVector, EPackageType> GetGrid() const { return Grid; } 
	FIntVector WorldToGridLocation(FVector WorldLocation) const;

	UFUNCTION(BlueprintCallable)
	FVector GridToWorldLocation(FIntVector GridLocation) const;

	static FIntVector RoundFVectorToIntVector(FVector Vector);
	FVector SnapLocationToGrid(FVector WorldLocation) const;
	FIntVector CalculatePackageOffset(FGridRange Range) const;
	bool CheckRangeVacant(FGridRange Range);
	bool CheckRangeVacantOrColor(FGridRange Range, EPackageType Color);
	bool CheckCellVacantOrColor(FIntVector Position, EPackageType Color);

	UFUNCTION(BlueprintCallable)
	void SetStatus(FGridRange Range, EPackageType Status);
	
	UFUNCTION(BlueprintCallable)
	void Setup(FGridParameters Parameters, FTransform LocalOffset);

	UFUNCTION(BlueprintCallable)
	void CalculatePackageBounds(FTransform PackageTransform, FVector LocalBoundMin, FVector LocalBoundsMax,
								FGridRange& OutRange) const;

	UFUNCTION(BlueprintCallable)
	bool FindSpaceForPackage(FTransform PackageTransform, UPARAM(ref) FGridRange& OutRange,UPARAM(ref) FTransform& OutTransform);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FIntVector Size;

	UPROPERTY(VisibleAnywhere)
	float CellSize;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FTransform GridTransform;

	UFUNCTION(BlueprintCallable)
	void UpdateDebug();
	
	FQuat SnapRotationToGrid(FRotator Rotator) const;
	FQuat SnapRotationToGridLocal(FRotator Rotator) const;
	
private:
	static float SnapRotationAxis(float Degrees);
	static FQuat SnapRotation(FRotator Rotation);
	bool FindAvailableGridPosition(FIntVector StartGridLocation, FIntVector& ResultPosition, FGridRange& OutRange);

	UPROPERTY(VisibleAnywhere)
	FColorLibrary ColorLibrary = FColorLibrary();
	
	UPROPERTY(EditAnywhere)
	bool bDebugGrid;
	
	UPROPERTY(VisibleAnywhere)
	TMap<FIntVector, EPackageType> Grid;
	
		
};
