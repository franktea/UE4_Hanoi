// Fill out your copyright notice in the Description page of Project Settings.


#include "PlateMover.h"
#include "DrawDebugHelpers.h"
#include "EngineUtils.h"

// Sets default values
APlateMover::APlateMover()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APlateMover::BeginPlay()
{
	Super::BeginPlay();
    
    auto FindPoleByName = [this](FString Name)->APole*{
        for(TActorIterator<APole> it(GetWorld()); it; ++it)
        {
            if(it->GetName() == Name)
            {
                UE_LOG(LogTemp, Warning, TEXT("find %s"), *Name);
                return *it;
            }
        }
        
        UE_LOG(LogTemp, Warning, TEXT("NOT FOUND %s"), *Name);
        return nullptr;
    };
    
    PoleA = FindPoleByName(TEXT("PoleA"));
    PoleB = FindPoleByName(TEXT("PoleB"));
    PoleC = FindPoleByName(TEXT("PoleC"));
    
  /*  FTimerHandle UnusedHandle;
    GetWorldTimerManager().SetTimer(UnusedHandle, [this](){
        Sequence.SetPoles(PoleA, PoleB, PoleC);
    }, 3.0, false);
   */
    GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
    widget = SNew(SVerticalBox) +
        SVerticalBox::Slot().HAlign(HAlign_Center)
        .VAlign(VAlign_Bottom)
        [
            SNew(SButton).OnClicked(FOnClicked::CreateUObject(this, &APlateMover::ButtonClicked))
            .Content()[
                SNew(STextBlock).Text(FText::FromString(TEXT("Start Moving")))
            ]
         ];
    GEngine->GameViewport->AddViewportWidgetForPlayer(GetWorld()->GetFirstPlayerController()->GetLocalPlayer(), widget.ToSharedRef(), 1);
}

FReply APlateMover::ButtonClicked()
{
    UE_LOG(LogTemp, Warning, TEXT("clicked"));
    widget->SetVisibility(EVisibility::Hidden);
    Sequence.SetPoles(PoleA, PoleB, PoleC);
    return FReply::Handled();
}

// Called every frame
void APlateMover::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
    Sequence.RunInTick(DeltaTime);
}

void APlateMover::MovePlateTo(APlate* ThePlate, FVector To)
{
    //TODO: set satemachine and brunning state
}

void APlateMover::TestMoveFromToPole()
{
    if(!PoleA || !PoleB)
    {
        UE_LOG(LogTemp, Warning, TEXT("PoleA or PoleB is null"));
        return;
    }
    
    if(PoleA->Plates.Num() == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("No plates on PoleA"));
        return;
    }
    
    APlate* DestPlate = PoleA->Plates.Last();
    PoleA->Plates.RemoveAt(PoleA->Plates.Num()-1);
    FVector DestVector = PoleB->GetActorLocation();
    DestVector.Z = 25.0 + PoleB->Plates.Num() * 10.0;
    PoleB->Plates.Add(DestPlate);
    DestPlate->SetActorLocation(DestVector);
}

void APlateMover::TestMoveFromToPole2()
{
    if(!PoleA || !PoleB)
    {
        UE_LOG(LogTemp, Warning, TEXT("PoleA or PoleB is null"));
        return;
    }
    
    if(PoleB->Plates.Num() == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("No plates on PoleB"));
        return;
    }
    
    APlate* DestPlate = PoleB->Plates.Last();
    PoleB->Plates.RemoveAt(PoleB->Plates.Num()-1);
    FVector DestVector = PoleA->GetActorLocation();
    DestVector.Z = 25.0 + PoleA->Plates.Num() * 10.0;
    PoleA->Plates.Add(DestPlate);
    DestPlate->SetActorLocation(DestVector);
}
