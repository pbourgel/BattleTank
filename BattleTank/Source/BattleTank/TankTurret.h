// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 *  Represents the turret and its rotation code called by TankAimingComponent
 */
UCLASS(meta=(BlueprintSpawnableComponent), hidecategories = ("Collision"))
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
    GENERATED_BODY()
    
public:
    //-1 is max counterclockwise movement, +1 is max clockwise (facing forward is "noon")
    void TurretRotate(float relativeSpeed);
    
private:
    UPROPERTY(EditDefaultsOnly, Category = Setup)
    float MaxDegreesPerSecond = 25.0f;
    
//    UPROPERTY(EditAnywhere, Category = Setup)
//    float MaxRotationDegrees = 360.0f;
//    
//    UPROPERTY(EditAnywhere, Category = Setup)
//    float MinRotationDegrees = 0.0f;
    
};
