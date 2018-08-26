// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"     //Must be the last include!

class ATank;

/**
 * Handles the raycasting through the player screen to figure out where
 * the tank turret should rotate/elevate to.
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

    virtual void BeginPlay() override;
	
    virtual void Tick(float DeltaTime) override;
    
private:
    ATank* PlayerTank;
    
    //Start the tank moving the barrel so that a shot would hit where the crosshair intersects the world
    void AimTowardsCrosshair();
    
    bool GetSightRayHitLocation(FVector & OutHitLocation) const;
    
    UPROPERTY(EditDefaultsOnly)
    float CrossHairXLocation = 0.5f;
    
    UPROPERTY(EditDefaultsOnly)
    float CrossHairYLocation = 0.33333f;
    
    UPROPERTY(EditDefaultsOnly)
    float lineTraceRange = 1000000.0f;
    
    bool GetLookDirection(FVector2D worldLocation, FVector& lookDirection) const;
    
    bool GetLookVectorHitLocation(FVector& hitLocation, FVector lookDirection) const;
    
protected:
    UFUNCTION(BlueprintCallable, Category = Setup)
    ATank* GetControlledTank() const;
    
};
