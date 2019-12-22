// Fill out your copyright notice in the Description page of Project Settings.


#include "HanoiTowerGameModeBase.h"
#include "EngineUtils.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "PlateMover.h"

AHanoiTowerGameModeBase::AHanoiTowerGameModeBase()
{
    DefaultPawnClass = APlateMover::StaticClass();
}

void AHanoiTowerGameModeBase::BeginPlay()
{
    Super::BeginPlay();
    
    auto FindCamera = [this]()->ACameraActor*{
        for(TActorIterator<ACameraActor> it(GetWorld()); it; ++it)
        {
            if(it->GetName() == TEXT("HanoiCamera"))
            {
                return *it;
            }
        }
        
        return nullptr;
    };
    
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
    if(!PlayerController)
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerController is null"));
        return;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Found Player controller"));
    }
    
    ACameraActor* Camera = FindCamera();
    if(Camera)
    {
        PlayerController->SetViewTarget(Camera);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("camera not found"));
    }
}
