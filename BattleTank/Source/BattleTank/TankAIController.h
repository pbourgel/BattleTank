// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
    
    virtual void BeginPlay() override;
    
    virtual void Tick(float DeltaTime) override;
    
private:
    UTankAimingComponent* AITankAiming;
    APawn* AITank;
    
    //How close can the AI Tank get to the player before stopping?
    UPROPERTY(EditDefaultsOnly)
    float AcceptanceRadius = 3000.0f;

    
};
