// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "Tank.h"
#include "CoreMinimal.h"
#include "AIController.h"
//#include "TankPlayerController.h"
#include "TankAIController.generated.h"

class ATank;

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
    ATank* AITank;
    ATank* PlayerTank;
    
    //How close can the AI Tank get to the player before stopping?
    UPROPERTY(EditDefaultsOnly)
    float AcceptanceRadius = 3000.0f;

    
};
