// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * UTankTrack applies driving forces to the tank tracks.
 */
UCLASS(meta=(BlueprintSpawnableComponent), hidecategories = ("Collision"))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
    UFUNCTION(BlueprintCallable, Category = Input)
    void SetThrottle(float throttleValue);
	
    //Max force per track in newtons
    UPROPERTY(EditDefaultsOnly)
    float TrackMaxDrivingForce = 45000000.0;
};
