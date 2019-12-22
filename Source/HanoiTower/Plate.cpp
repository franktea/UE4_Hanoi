// Fill out your copyright notice in the Description page of Project Settings.


#include "Plate.h"

// Sets default values
APlate::APlate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Plate Mesh");
    RootComponent = Mesh;
    Mesh->SetSimulatePhysics(true);
    Mesh->SetEnableGravity(true);
}

// Called when the game starts or when spawned
void APlate::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

