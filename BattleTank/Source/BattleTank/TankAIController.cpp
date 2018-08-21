// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAIController.h"

ATank* ATankAIController::GetControlledTank() const
{
    APawn* pwn = GetPawn();
    if(!pwn) { return nullptr; }
    return Cast<ATank>(pwn);
}

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
    
    AITank = GetControlledTank();
    
    
    if(AITank != nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("TankAIController: GetControlledTank() possessing %s"), *(AITank->GetName()));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("TankAIController not possessing a tank"));
    }
    
    PlayerTank = GetPlayerTank();
    if(PlayerTank != nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("TankAIController: Found player Tank %s"), *(PlayerTank->GetName()));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("TankAIController: Player Tank not found"));
    }
}

void ATankAIController::Tick(float DeltaTime)
{
    if(PlayerTank != nullptr)
    {
        //TODO: Move towards the player
        
        //Start aiming towards the player
        GetControlledTank()->AimAt(PlayerTank->GetActorLocation());
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("%s has nothing to aim at"), *(GetName()));
    }
}

ATank* ATankAIController::GetPlayerTank() const
{
    APawn* pwn = GetWorld()->GetFirstPlayerController()->GetPawn();
    if(!pwn) { return nullptr; }
    return Cast<ATank>(pwn);
    
}
