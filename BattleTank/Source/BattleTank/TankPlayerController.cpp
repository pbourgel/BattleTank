// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();
    PlayerTank = GetControlledTank();
    if(PlayerTank != nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("GetControlledTank() possessing %s"), *(PlayerTank->GetName()));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("TankPlayerController not possessing a tank"));
    }
    UE_LOG(LogTemp, Warning, TEXT("TankPlayerController BeginPlay()"));
}

