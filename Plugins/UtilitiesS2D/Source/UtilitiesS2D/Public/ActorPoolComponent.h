// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActorPoolComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UTILITIESS2D_API UActorPoolComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UActorPoolComponent();

protected:
	virtual void BeginPlay() override;
	void InitializeNewPooledActor();

public:	
	UFUNCTION(BlueprintCallable)
	UStaticMeshComponent* GetPooledActor();

	UFUNCTION(BlueprintCallable)
	void ClearPooledActors();

private:
	UPROPERTY(VisibleAnywhere)
	TArray<UStaticMeshComponent*> ActorPool;

	UPROPERTY(VisibleAnywhere)
	TArray<UStaticMeshComponent*> ActiveActors;

	UPROPERTY(EditAnywhere)
	int PreWarmed = 4;
		
};
