// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericActorPoolComponent.h"
#include "GameFramework/Actor.h"
#include "PoolActor.generated.h"

UCLASS()
class UTILITIESS2D_API APoolActor : public AActor
{
	GENERATED_BODY()

	
public:
	APoolActor();

	UFUNCTION(BlueprintCallable)
	void Release(bool bForce = false);
	void Activate(bool bForce = false);
	virtual void LifeSpanExpired() override { Release(); }
	void SetPool(UGenericActorPoolComponent* NewPool) { Pool = NewPool; }

protected:
	virtual void OnReleased() {}
	virtual void OnActivated() {}
	
	UPROPERTY()
	UGenericActorPoolComponent* Pool;
	bool bActivated = false;
};
