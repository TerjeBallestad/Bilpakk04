// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorPoolComponent.h"
#include "BilpakkLevelData.h"
#include "PackageGrid.h"
#include "PackagePointsCalculator.h"
#include "StackablePackage.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h"
#include "GameState/GameStateBilpakk.h"
#include "PlayfieldContainer.generated.h"

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPointsAddedSignature);

UCLASS()
class BILPAKK04_API APlayfieldContainer : public AActor
{
	GENERATED_BODY()

public:
	APlayfieldContainer();

	UPROPERTY(BlueprintReadOnly)
	AGameStateBilpakk* GameState;

protected:
	virtual void BeginPlay() override;

public:
	bool PlacePackage(const AStackablePackage* ActivePackage);
	void StartUpdatingPreview(UMaterialInstance* Material, UStaticMesh* Mesh);
	void StopUpdatingPreview();
	bool UpdatePreview(const AStackablePackage* ActivePackage, FTransform& InOutPreviewTransform);

	UFUNCTION(BlueprintCallable)
	void Setup() const;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FPoints Points;

	UPROPERTY(EditDefaultsOnly)
	float PreviewMovementThreshold = 0.1;

	UPROPERTY(BlueprintAssignable)
	FPointsAddedSignature OnPointsAddedDelegate;
	
	UPROPERTY()
	bool bUpdatePreview = false;

	UPROPERTY()
	AActor* PreviewActor;

	UPROPERTY()
	FTransform PreviousPreviewTransform;

	UPROPERTY()
	FGridRange PreviewRange;

	UPROPERTY(BlueprintReadOnly)
	UStaticMeshComponent* PreviewMesh;

	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UActorPoolComponent* StaticMeshPool;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* CarModel;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UPackageGrid* Grid;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UWidgetComponent* FloatingTextWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UWidgetComponent* NegativeFloatingTextWidget;

	UPROPERTY(VisibleAnywhere)
	UPackagePointsCalculator* PointsCalculator;


};
