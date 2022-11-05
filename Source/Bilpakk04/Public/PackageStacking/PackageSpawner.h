// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
};
