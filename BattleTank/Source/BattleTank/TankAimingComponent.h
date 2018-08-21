// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//Forward declaration
class UTankBarrel;

//Holds barrel's parameters and Elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();
    void AimAt(FVector aimLocation, float launchSpeed);
    
    void SetBarrelReference(UTankBarrel* barrelToSet);
    //TODO: Add set turren reference (why did Ben add this if we already have a pointer and a method for this?)
//protected:
//    // Called when the game starts
//    virtual void BeginPlay() override;
//
public:    
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    
    UTankBarrel* tankBarrel;
    
    void MoveBarrelTowards(FVector aimDirection);
    
};
