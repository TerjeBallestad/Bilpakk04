// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GenericActorPoolComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UTILITIESS2D_API UGenericActorPoolComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:
	class APoolActor* Spawn(TSubclassOf<APoolActor> Class, const FTransform& Transform, const struct FActorSpawnParameters& SpawnParameters);

	template <class T>
	T* Spawn(const TSubclassOf<APoolActor> Class, const FTransform& Transform, const struct FActorSpawnParameters& SpawnParameters)
	{
		static_assert(TIsDerivedFrom<T, APoolActor>::IsDerived, "");
		return Cast<T>(Spawn(Class, Transform, SpawnParameters));
	}

	void Release(APoolActor* Actor);

private:
	void BeginPlay() override;

	// Here, the class will be created beforehand.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	TMap<TSubclassOf<APoolActor>, uint8> Reserve;
	TMap<TSubclassOf<APoolActor>, TArray<TWeakObjectPtr<APoolActor>>> Pool;

#if !UE_BUILD_SHIPPING
	// It remembers the number of actors registered in the actor pool when it was the most numerous, and outputs the log when the game ends
	// You only need to reserve the actor as long as it appears in the output log.
	// Attention: 사터가 삭제다의 사랑다의 사랑다. 삭제다다 다이 이이스트.
	TMap<TSubclassOf<APoolActor>, uint8> MaxUse;
	TMap<TSubclassOf<APoolActor>, uint8> CurUse;
	void EndPlay(EEndPlayReason::Type EndPlayReason) override;
	void UpdateMaxUse(TSubclassOf<APoolActor> Class, uint8 Cur);
#endif
};

