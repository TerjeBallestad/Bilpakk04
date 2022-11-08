// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/BilpakkLevelData.h"
#include "Data/BilpakkVehicleData.h"
#include "StateMachine/StateManager.h"
#include "GameFramework/GameStateBase.h"
#include "GameStateBilpakk.generated.h"

/**
 * 
 */
UCLASS()
class BILPAKK04_API AGameStateBilpakk : public AGameStateBase
{
	GENERATED_BODY()


public:
	
	AGameStateBilpakk();
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UDataTable* LevelDataTable;

	UPROPERTY(EditAnywhere)
	UBilpakkVehicleData* VehicleData = nullptr;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UBilpakkVehicleData> VehicleDataClass;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString RowName;

	UPROPERTY(EditAnywhere)
	UStateManager* StateManager;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FBilpakkLevelData LevelData;

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	static FBilpakkLevelData GetLevelData(const UObject* WorldContextObject);

	// UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	// UBilpakkVehicleData* GetVehicleData(const UObject* WorldContextObject);

	// Points
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	static int32 GetPoints(const UObject* WorldContextObject);

	UFUNCTION()
	void SetPoints(int32 Amount);

	UFUNCTION()
	void SetBonusPoints(int32 Amount);

	UFUNCTION()
	void AddBonusPoints(int32 Amount);

	// Gameplay actor references
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class APackageSpawner* PackageSpawner;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class APlayfieldContainer* PlayfieldContainer;

private:
	int32 Points;
	int32 BonusPoints;
};

