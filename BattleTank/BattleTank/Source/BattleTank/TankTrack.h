// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

class ASprungWheel;

/**
 * UTankTrack applies driving forces to the tank tracks.
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
    UFUNCTION(BlueprintCallable, Category = Input)
    void SetThrottle(float throttleValue);
	
    //Max force per track in newtons
    UPROPERTY(EditDefaultsOnly)
    float TrackMaxDrivingForce = 45000000.0;
    
    //virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    
    virtual void BeginPlay() override;
    
    virtual void OnRegister() override;
    
private:
    UTankTrack();
     
    void DriveTrack(float currentThrottle);
    
    TArray<ASprungWheel*> GetWheels() const;
    
};
