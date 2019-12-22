// Fill out your copyright notice in the Description page of Project Settings.


#include "Pole.h"

// Sets default values
APole::APole()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Pole Mesh");
    RootComponent = Mesh;
}

// Called when the game starts or when spawned
void APole::BeginPlay()
{
	Super::BeginPlay();
	
    if(Plates.Num() > 0)
    {
        FTimerHandle UnusedHandle;
        GetWorldTimerManager().SetTimer(UnusedHandle, this, &APole::ShowPlateZ, 1.0f, false);
    }
}

// Called every frame
void APole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APole::ShowPlateZ()
{
    for(APlate* p: Plates)
    {
        UE_LOG(LogTemp, Warning, TEXT("%s"), *p->GetActorLocation().ToString());
    }
}

