// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Enum for aiming state
UENUM()
enum class EFiringStatus : uint8
{
    Reloading,
    Aiming,
    Locked
};

//Forward declaration
class UTankBarrel;
class UTankTurret;
class AProjectile;

/*
 * Executes aiming movements and related calculations for both the player and AI tanks.
 * Sets references to the barrel and turret objects.
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();
    void AimAt(FVector aimLocation);
    
    void SetBarrelReference(UTankBarrel* barrelToSet);
    
    void SetTurretReference(UTankTurret* turretToSet);
    
    UFUNCTION(BlueprintCallable, Category = Setup)
    void Initialize(UTankTurret* turretToSet, UTankBarrel* barrelToSet);
    
    //TODO: Add set turret reference (why did Ben add this if we already have a pointer and a method for this?)
//protected:
    // Called when the game starts
    virtual void BeginPlay() override;

public:    
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UFUNCTION(BlueprintCallable, Category = Setup)
    void Fire();
    
protected:
    //Needs to be protected so we can expose it to Blueprints
    UPROPERTY(BlueprintReadOnly, Category = State)
    EFiringStatus firingState = EFiringStatus::Reloading;
    
    UPROPERTY(EditDefaultsOnly, Category = Firing)
    float launchSpeed = 4000.0f; //The ting goes BOOM
    

    
private:
    
    UTankBarrel* tankBarrel = nullptr;
    
    UTankTurret* tankTurret = nullptr;
    
    void MoveBarrelTowards(FVector aimDirection);
    
    void MoveTurretTowards(FVector aimDirection);
    
    double lastFireTime = 0;
    
    UPROPERTY(EditDefaultsOnly, Category = Firing)
    float reloadTimeInSeconds = 3.0f;
    
    // https://docs.unrealengine.com/latest/INT/Programming/UnrealArchitecture/TSubclassOf
    UPROPERTY(EditDefaultsOnly, Category = Setup)
    TSubclassOf<AProjectile> projectileBlueprint;    //Alternative (see above) is TSubclassOf<UDamageType>
    
    bool IsBarrelMoving();
    
};
