// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"  //This must be the last include!

//Forward declarations
class UTankBarrel;



/*
 * Handles firing and calls aiming functions on UTankAimingComponent.
 * This class keeps track of variables such as projectile launch speed and time to reload.
 */
UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    

    
public:	

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    //void AimAt(FVector aimLocation);
    
//    UFUNCTION(BlueprintCallable, Category = Setup)
//    void SetBarrelReference(UTankBarrel* barrelToSet);
//    
//    UFUNCTION(BlueprintCallable, Category = Setup)
//    void SetTurretReference(UTankTurret* turretToSet);
    
    //TODO Remove once firing is moved to aiming component
    //UPROPERTY(EditDefaultsOnly, Category = Firing)
    //float launchSpeed = 4000.0f; //The ting goes BOOM
    
private:
    

    
    //Local barrel reference for spawning projectile
   // UTankBarrel* tankBarrel = nullptr;      //TODO: Remove barrel

};
