// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BilpakkLevelData.h"
#include "HandController.h"
#include "GenericActorPool/PoolActor.h"
#include "StackablePackage.generated.h"

/**
 * 
 */
UCLASS()
class BILPAKK04_API AStackablePackage : public APoolActor
{
	GENERATED_BODY()

public:
	AStackablePackage();

	UPROPERTY()
	bool bIsGripped = false;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FPackageParameters PackageParameters;

	UPROPERTY(EditDefaultsOnly)
	UMaterial *HoloMaterial;

	UPROPERTY(EditDefaultsOnly)
	UMaterial *RedHoloMaterial;

	UFUNCTION(BlueprintCallable)
	void Setup(FPackageParameters NewPackage);
	
	void StopInteract();
	void StartInteract(AHandController* HandController);
};
