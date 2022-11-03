// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorPoolComponent.h"

UActorPoolComponent::UActorPoolComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UActorPoolComponent::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < PreWarmed; ++i)
	{
		InitializeNewPooledActor();
	}
}

void UActorPoolComponent::InitializeNewPooledActor()
{
	UStaticMeshComponent* Mesh = NewObject<UStaticMeshComponent>(GetOwner());
	Mesh->RegisterComponent();
	Mesh->SetVisibility(false);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ActorPool.Add(Mesh);
	UE_LOG(LogTemp, Warning, TEXT("%d elements from %s"), ActorPool.Num(), *GetOwner()->GetName())
}

UStaticMeshComponent* UActorPoolComponent::GetPooledActor()
{
	if (ActorPool.Num() < 1)
	{
		InitializeNewPooledActor();
	}
	UStaticMeshComponent* Mesh = ActorPool.Pop(false);
	if (!Mesh) return nullptr;
	Mesh->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	Mesh->SetVisibility(true);
	ActiveActors.Add(Mesh);

	return Mesh;
}

void UActorPoolComponent::ClearPooledActors()
{
	for (auto Mesh : ActiveActors)
	{
		Mesh->SetVisibility(false);
		Mesh->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
		ActorPool.Add(Mesh);
	}
	ActiveActors.Empty(ActorPool.Num());
}
