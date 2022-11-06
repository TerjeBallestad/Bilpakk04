// Fill out your copyright notice in the Description page of Project Settings.


#include "GenericActorPool/PoolActor.h"

APoolActor::APoolActor()
{
	PrimaryActorTick.bCanEverTick = false;

}

void APoolActor::Release(bool bForce)
{
	if (!bActivated && !bForce) return;
	SetActorTickEnabled(false);
	SetActorEnableCollision(false);
	SetActorHiddenInGame(true);
	bActivated = false;
	Pool->Release(this);
	OnReleased();
}

void APoolActor::Activate(const bool bForce)
{
	if (bActivated && !bForce) return;
	SetActorTickEnabled(true);
	SetActorEnableCollision(true);
	SetActorHiddenInGame(false);
	bActivated = true;
	OnActivated();
}

