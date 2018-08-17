// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();
    PlayerTank = GetControlledTank();
    if(PlayerTank != nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("TankPlayerController: GetControlledTank() possessing %s"), *(PlayerTank->GetName()));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("TankPlayerController not possessing a tank"));
    }
}

void ATankPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    //UE_LOG(LogTemp, Warning, TEXT("In Tick() in TankPlayerController"));
    AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
    APawn* pwn = GetPawn();
    if(!pwn) { return nullptr; }
    return Cast<ATank>(pwn);
}

void ATankPlayerController::AimTowardsCrosshair()
{
    //We aren't aiming anything if we haven't possessed a tank
    if(!GetControlledTank()) return;
    
    //Get world location if linetrace through crosshair
    //If it hits the landscape
        //Tell controlled tank to aim at this point
    
}

