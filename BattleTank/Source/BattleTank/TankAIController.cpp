// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
//#include "Tank.h"

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
    
    APawn* playerTankPwn = GetWorld()->GetFirstPlayerController()->GetPawn();
    AITank = GetPawn();
    
    if(!ensure(playerTankPwn && AITank)) { return; }
    
    //TODO: Move towards the player
    MoveToActor(Cast<AActor>(playerTankPwn), AcceptanceRadius, true, true, false);  //TODO: Check radius is in centimeters
        
    AITankAiming = AITank->FindComponentByClass<UTankAimingComponent>();
        
    //Start aiming towards the player
    AITankAiming->AimAt(playerTankPwn->GetActorLocation());
        
    //Fire at player
    //TODO: Fix Firing
    AITankAiming->Fire();
    
}

