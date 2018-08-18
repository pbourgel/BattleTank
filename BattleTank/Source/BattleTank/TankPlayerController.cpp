// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Math/Vector.h"

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
    
    FVector HitLocation;

    //UE_LOG(LogTemp, Warning, TEXT("Hitlocation: %s"),*HitLocation.ToString());
    
    //Get world location of linetrace through crosshair (in Unityspeak this is a ScreenToPointRay raycast at the crosshair)
    if(GetSightRayHitLocation(HitLocation)) //Side-effect: Performs raytrace and stores location of object hit in HitLocation
    {
        //If it hits the landscape
        //Tell controlled tank to aim at this point
    }

    
}

//Get world location of linetrace through crosshair, return true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{

    FVector playerLocation;
    FRotator playerRotation;
    //(in Unityspeak this is a ScreenToPointRay raycast at the crosshair)
    //if we did hit something, return true
    if(true)
    {
        OutHitLocation = FVector(1.0);
        return true;
    }
    //else return false
    else {return false;}
}
