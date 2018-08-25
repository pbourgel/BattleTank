// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 * Responsible for driving tank tracks.
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:
    //Throw = how far forward or back the control is moved
    UFUNCTION(BlueprintCallable, Category = Input)
    void IntendMoveForward(float Throw);
	
    UFUNCTION(BlueprintCallable, Category = Input)
    void IntendTurnRight(float Throw);
    
    
    UFUNCTION(BlueprintCallable, Category = Setup)
    void Initialize(UTankTrack* leftTrackToSet, UTankTrack* rightTrackToSet);
    
private:
    
    //UPROPERTY()
    UTankTrack* LeftTrack = nullptr;
    
    //UPROPERTY()
    UTankTrack* RightTrack = nullptr;

    
};
