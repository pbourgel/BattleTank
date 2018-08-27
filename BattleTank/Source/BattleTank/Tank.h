// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
//#include "TankAimingComponent.h"
#include "Tank.generated.h"  //This must be the last include!

//Forward declarations
class UTankBarrel;
class UTankAimingComponent;
class UTankMovementComponent;
class UTankTurret;
class AProjectile;

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
    
    UFUNCTION(BlueprintCallable, Category = Setup)
    void Fire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    
    UPROPERTY(BlueprintReadOnly)
    UTankAimingComponent* aimingComponent = nullptr;
    
    UPROPERTY(BlueprintReadOnly)
    UTankMovementComponent* movementComponent = nullptr;
    
public:	

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    void AimAt(FVector aimLocation);
    
//    UFUNCTION(BlueprintCallable, Category = Setup)
//    void SetBarrelReference(UTankBarrel* barrelToSet);
//    
//    UFUNCTION(BlueprintCallable, Category = Setup)
//    void SetTurretReference(UTankTurret* turretToSet);
    
    UPROPERTY(EditDefaultsOnly, Category = Firing)
    float launchSpeed = 4000.0f; //The ting goes BOOM
    
    UPROPERTY(EditDefaultsOnly, Category = Firing)
    float reloadTimeInSeconds = 3.0f;
private:
    
    // https://docs.unrealengine.com/latest/INT/Programming/UnrealArchitecture/TSubclassOf
    UPROPERTY(EditDefaultsOnly, Category = Setup)
    TSubclassOf<AProjectile> projectileBlueprint;    //Alternative (see above) is TSubclassOf<UDamageType>
    
    //Local barrel reference for spawning projectile
    UTankBarrel* tankBarrel = nullptr;      //TODO: Remove barrel
    
    double lastFireTime = 0;
};
