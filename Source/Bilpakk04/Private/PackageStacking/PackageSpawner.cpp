// Fill out your copyright notice in the Description page of Project Settings.


#include "PackageStacking/PackageSpawner.h"

APackageSpawner::APackageSpawner()
{
	PrimaryActorTick.bCanEverTick = false;

	PackagePool = CreateDefaultSubobject<UGenericActorPoolComponent>(TEXT("PackagePool"));

}

void APackageSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}



