// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Plate.h"
#include "Pole.h"
#include <vector>
#include <memory>

// move top plate from a to b
/////////////////////////////////////////////////////////////////////////////////
// V_BEGINTOP------------------------>VENDTOP
//      ^                                |
//      |                                |
//      |                                |
//      |                                |
//      |                                |
//      |                                v
//   V_BEGIN                            V_END
struct OneMove
{
private:
    APole* FromPole;
    APole* ToPole;
    float TotalTime;
    APlate* CurrentPlate;
private:
    FVector V_Begin;
    FVector V_End;
    FVector V_BeginTop;
    FVector V_EndTop;
    float T1;
    float T2;
    FVector Start_T1;
    FVector T1_T2;
    FVector T2_End;
public:
    OneMove(APole* From, APole* To): FromPole(From), ToPole(To), TotalTime(0),
        CurrentPlate(nullptr)
    {
        if(From->Plates.Num() == 0)
        {
            return;
        }
        
        CurrentPlate = From->Plates.Last();
        CurrentPlate->Mesh->SetSimulatePhysics(false);
        CurrentPlate->Mesh->SetEnableGravity(false);
        V_Begin = CurrentPlate->GetActorLocation();
        V_End = To->GetActorLocation();
        V_End.Z += 25 + To->Plates.Num()*10.1f;
        V_BeginTop = V_Begin;
        V_BeginTop.Z = 200.f;
        V_EndTop = V_End;
        V_EndTop.Z = 200.f;
        
        Start_T1 = V_BeginTop - V_Begin;
        T1_T2 = V_EndTop - V_BeginTop;
        T2_End = V_End - V_EndTop;
        
        float TotalLen = Start_T1.Size() + T1_T2.Size() + T2_End.Size();
        T1 = Start_T1.Size() / TotalLen;
        T2 = T1 + T1_T2.Size() / TotalLen;
        
        
        From->Plates.RemoveAt(From->Plates.Num()-1);
        To->Plates.Add(CurrentPlate);
    }
public:
    bool MoveDelta(float DeltaTime); // if done, return false
};

class HANOITOWER_API MoveSequence
{
private:
    bool bInited = false;
    bool bFinished = false;
    APole* PoleA = nullptr;
    APole* PoleB = nullptr;
    APole* PoleC = nullptr;
    std::unique_ptr<OneMove> CurrentMove;
    std::vector<std::pair<APole*, APole*>> All;
    const float V = 100.0; // v = 100.0 cm/s
public:
	MoveSequence();
	~MoveSequence();
public:
    void SetPoles(APole* PA, APole* PB, APole* PC);
    void RunInTick(float DeltaTime);
private:
    void NextMove();
};
