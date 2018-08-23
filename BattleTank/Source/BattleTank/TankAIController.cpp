// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
//    if(AITank != nullptr)
//    {
//        UE_LOG(LogTemp, Warning, TEXT("TankAIController: GetControlledTank() possessing %s"), *(AITank->GetName()));
//    }
//    else
//    {
//        UE_LOG(LogTemp, Error, TEXT("TankAIController not possessing a tank"));
//    }
//
//    PlayerTank = GetPlayerTank();
//    if(PlayerTank != nullptr)
//    {
//        UE_LOG(LogTemp, Warning, TEXT("TankAIController: Found player Tank %s"), *(PlayerTank->GetName()));
//    }
//    else
//    {
//        UE_LOG(LogTemp, Error, TEXT("TankAIController: Player Tank not found"));
//    }
}

void ATankAIController::Tick(float DeltaTime)
{
    
    APawn* tankPwn = GetWorld()->GetFirstPlayerController()->GetPawn();
    if(!tankPwn) { return; }
    PlayerTank = Cast<ATank>(tankPwn);
    
    if(PlayerTank != nullptr)
    {
        //TODO: Move towards the player
         
        APawn* pwn = GetPawn();
        if(!pwn) { return; }
        AITank = Cast<ATank>(pwn);
        
        //Start aiming towards the player
        AITank->AimAt(PlayerTank->GetActorLocation());
        
        //Fire at player
        AITank->Fire();     
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("%s has nothing to aim at"), *(GetName()));
    }
}
