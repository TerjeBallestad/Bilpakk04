// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BilpakkLevelData.h"
#include "StackablePackage.h"
#include "GameFramework/Actor.h"
#include "GenericActorPool/GenericActorPoolComponent.h"
#include "PackageSpawner.generated.h"

UCLASS()
class BILPAKK04_API APackageSpawner : public AActor
{
	GENERATED_BODY()

public:
	APackageSpawner();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditDefaultsOnly)
	UGenericActorPoolComponent* PackagePool;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FPackageParameters> SpawnQueue;

	UFUNCTION(BlueprintCallable)
	void Setup();

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	static int32 GetRemainingPackageAmount(UObject* WorldContextObject);

private:
	UPROPERTY(EditDefaultsOnly)
	FTransform PackageSpawnLocation;

	UFUNCTION(BlueprintCallable)
	AStackablePackage* GetNextPackage();
	void RemoveFirstPackageFromQueue();

	void ShuffleArray(TArray<FPackageParameters>& Array) const;

	UPROPERTY(VisibleAnywhere)
	TMap<EPackageType, UMaterialInstance*> Materials;

	UPROPERTY(VisibleAnywhere)
	FColorLibrary ColorLibrary = FColorLibrary();

	UPROPERTY(EditAnywhere)
	UMaterialInterface* MaterialClass;

	UPROPERTY(VisibleAnywhere)
	TMap<EPackageSize, FPackageParameters> PackageLibrary;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AStackablePackage> PackageClass;
};
