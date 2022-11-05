// Copyright 2019 Seokjin Lee. All Rights Reserved.

#include "GenericActorPool/GenericActorPoolComponent.h"
#include "Engine/World.h"
#include "GenericActorPool/PoolActor.h"

DEFINE_LOG_CATEGORY_STATIC(LogActorPool, Log, All)

APoolActor* UGenericActorPoolComponent::Spawn(const TSubclassOf<APoolActor> Class, const FTransform& Transform, const FActorSpawnParameters& SpawnParameters)
{
	const auto SpawnImpl = [&]()->APoolActor*
	{
		if (!Class)
		{
			UE_LOG(LogActorPool, Error, TEXT(__FUNCTION__" : Failed to spawn actor. Class was nullptr."));
			return nullptr;
		}

		if (const auto PoolPtr = Pool.Find(Class))
		{
			while (PoolPtr->Num() > 0)
			{
				if (const auto Actor = PoolPtr->Pop().Get())
				{
					Actor->SetOwner(SpawnParameters.Owner);
					Actor->SetInstigator(SpawnParameters.Instigator);
					Actor->SetActorTransform(GetDefault<AActor>(Class)->GetRootComponent()->GetRelativeTransform() * Transform);
					Actor->Activate();
					return Actor;
				}
			}
		}

		if (const auto Actor = static_cast<APoolActor*>(GetWorld()->SpawnActor(Class, &Transform, SpawnParameters)))
		{
			UE_LOG(LogActorPool, Warning,
			       TEXT("%sCreate a new actor because the actor pool is empty. We recommend that you register the class in Reserve.Maximum usage so far : %d"),
			       *Class->GetName(), MaxUse.FindOrAdd(Class) + 1);
			Actor->SetPool(this);
			Actor->Activate();
			return Actor;
		}

		return nullptr;
	};

	const auto Actor = SpawnImpl();
#if !UE_BUILD_SHIPPING
	if (Actor) UpdateMaxUse(Class, ++CurUse.FindOrAdd(Class));
#endif
	return Actor;
}

void UGenericActorPoolComponent::Release(APoolActor* Actor)
{
	const auto Class = Actor->GetClass();
	Pool.FindOrAdd(Class).Add(Actor);
#if !UE_BUILD_SHIPPING
	UpdateMaxUse(Class, --CurUse.FindOrAdd(Class));
#endif
}

void UGenericActorPoolComponent::BeginPlay()
{
	Super::BeginPlay();

	FActorSpawnParameters Parameters;
	Parameters.Owner = this->GetOwner();
	Parameters.bNoFail = true;

	for (const auto& Pair : Reserve)
	{
		Pool.FindOrAdd(Pair.Key).Reserve(Pair.Value);

		for (auto i = 0; i < Pair.Value; ++i)
		{
			if (const auto Actor = static_cast<APoolActor*>(GetWorld()->SpawnActor(Pair.Key, &FTransform::Identity, Parameters)))
			{
				Actor->SetPool(this);
				Actor->Release(true);
			}
		}

#if !UE_BUILD_SHIPPING
		if (const auto P = CurUse.Find(Pair.Key)) *P = 0;
		if (const auto P = MaxUse.Find(Pair.Key)) *P = 0;
#endif
	}
}

#if !UE_BUILD_SHIPPING
void UGenericActorPoolComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	for (const auto& Pair : MaxUse)
	{
		UE_LOG(LogActorPool, Log, TEXT("%s maximum concurrent use:"), *Pair.Key->GetName(), Pair.Value);
	}
}

void UGenericActorPoolComponent::UpdateMaxUse(const TSubclassOf<APoolActor> Class, const uint8 Cur)
{
	auto& Max = MaxUse.FindOrAdd(Class);
	if (Max < Cur) Max = Cur;
}
#endif