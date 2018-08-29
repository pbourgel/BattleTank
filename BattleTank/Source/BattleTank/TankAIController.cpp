// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
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

