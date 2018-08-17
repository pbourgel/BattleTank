// Fill out your copyright notice in the Description page of Project Settings.


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

ATank* ATankAIController::GetPlayerTank() const
{
    APawn* pwn = GetWorld()->GetFirstPlayerController()->GetPawn();
    if(!pwn) { return nullptr; }
    return Cast<ATank>(pwn);
    
}
