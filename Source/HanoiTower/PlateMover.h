// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Plate.h"
#include "Pole.h"
#include "MoveSequence.h"
#include "SlateBasics.h"
#include "SButton.h"
#include "STextBlock.h"
#include "Templates/SharedPointer.h" 
#include "PlateMover.generated.h"

UCLASS(Blueprintable)
class HANOITOWER_API APlateMover : public APawn
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	APlateMover();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    const float Max_Z = 220.f;
    
    void MovePlateTo(APlate* ThePlate, FVector To);

    void TestMoveFromToPole();
    void TestMoveFromToPole2();
public:
    UPROPERTY(EditAnywhere, Category = Poles)
    APole* PoleA;
    
    UPROPERTY(EditAnywhere, Category = Poles)
    APole* PoleB;
    
    UPROPERTY(EditAnywhere, Category = Poles)
    APole* PoleC;
private:
    MoveSequence Sequence;
    TSharedPtr<SVerticalBox> widget;
    FReply ButtonClicked();
};
