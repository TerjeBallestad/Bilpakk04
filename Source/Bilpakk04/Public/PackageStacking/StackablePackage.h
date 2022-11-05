// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* MeshComponent;
	
};
