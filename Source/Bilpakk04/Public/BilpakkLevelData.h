// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "BilpakkLevelData.generated.h"

UENUM(BlueprintType)
enum class EPackageSize : uint8
{
	OneFourOne UMETA(DisplayName = "1x4x1"),
	OneFourFour UMETA(DisplayName = "1x4x4"),
	TwoOneThree UMETA(DisplayName = "2x1x3"),
	TwoTwoTwo UMETA(DisplayName = "2x2x2"),
	TwoThreeThree UMETA(DisplayName = "2x3x3"),
	ThreeFourTwo UMETA(DisplayName = "3x4x2"),
};

UENUM(BlueprintType)
enum class EPackageType : uint8
{
	Vacant,
	Occupied,
	Tan,
	Purple,
	Blue,
	Yellow,
	White,
	Pink,
	SpringGreen,
	LightBlue,
	Green,
	Orange,
	DarkMagenta,
	Red,

	Count
};

ENUM_RANGE_BY_COUNT(EPackageType, EPackageType::Count);

USTRUCT(BlueprintType)
struct FColorLibrary
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Package Colors")
	TMap<EPackageType, FColor> Colors = {
		{EPackageType::Vacant, FColor(100, 100, 100)},
		{EPackageType::Occupied, FColor(0, 0, 0)},
		{EPackageType::Tan, FColor(198, 155, 109)},
		{EPackageType::Purple, FColor(135, 136, 238)},
		{EPackageType::Blue, FColor(0, 112, 221)},
		{EPackageType::Yellow, FColor(255, 244, 104)},
		{EPackageType::White, FColor(255, 255, 255)},
		{EPackageType::Pink, FColor(244, 140, 186)},
		{EPackageType::SpringGreen, FColor(0, 255, 152)},
		{EPackageType::LightBlue, FColor(63, 199, 235)},
		{EPackageType::Green, FColor(170, 211, 114)},
		{EPackageType::Orange, FColor(255, 124, 10)},
		{EPackageType::DarkMagenta, FColor(163, 48, 201)},
		{EPackageType::Red, FColor(196, 30, 58)},
	};
};

USTRUCT(BlueprintType)
struct FPackageAmounts
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Package Amounts")
	TMap<EPackageSize, int32> Amounts;
};

USTRUCT(BlueprintType)
struct FPackageParameters
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Package Parameters")
	EPackageSize SizeE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Package Parameters")
	FIntVector SizeInt;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Package Parameters")
	EPackageType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Package Parameters")
	UStaticMesh* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Package Parameters")
	UMaterialInstance* Material;
};

USTRUCT(BlueprintType)
struct FGridRange
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	FIntVector Min;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	FIntVector Max;
};

USTRUCT(BlueprintType)
struct FGridParameters
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	FIntVector Size;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	float CellSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	TArray<FGridRange> DefaultOccupiedGridPositions;
};

USTRUCT(BlueprintType)
struct FBilpakkLevelData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bilpakk Level")
	FText LevelName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bilpakk Level")
	int32 Difficulty;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bilpakk Level")
	FGridParameters GridParameters;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bilpakk Level")
	TMap<EPackageType, FPackageAmounts> PackageAmounts;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bilpakk Level")
	UStaticMesh* CarMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bilpakk Level")
	TMap<EPackageSize, FPackageParameters> PackageLibrary;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bilpakk Level")
	TArray<FGridRange> Doors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bilpakk Level")
	TAssetPtr<UTexture2D> MapImage;
};
