// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

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
    
    //Hi, you're probably here because Epic changed the signature for OnHit's delegate function.  The file you're probably looking for in the source is
    // Engine/UE4/Source/Runtime/Engine/Classes/Components/PrimitiveComponent.h
    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
    
    void ApplySidewaysForce();
    
    void DriveTrack();
    
    float currentThrottle = 0.0f;
};
