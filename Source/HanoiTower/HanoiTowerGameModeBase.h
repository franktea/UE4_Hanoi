// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "HanoiTowerGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class HANOITOWER_API AHanoiTowerGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
    AHanoiTowerGameModeBase();
    
    virtual void BeginPlay() override;
};
