// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Plate.h"

#include "Pole.generated.h"

UCLASS()
class HANOITOWER_API APole : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APole();

    void ShowPlateZ();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, Category="Pole Mesh")
    UStaticMeshComponent* Mesh;
    
    UPROPERTY(EditAnywhere, Category="Plates")
    TArray<APlate*> Plates;
};
