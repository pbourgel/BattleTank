// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    //No need to protect pointers as added at construction
    aimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("AimingComponent"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	

    
}

void ATank::Fire()
{
    bool bIsReloaded = (FPlatformTime::Seconds() - lastFireTime) > reloadTimeInSeconds;
    
    if(tankBarrel && bIsReloaded) {

        //Spawn a projectile at the socket location
        FTransform projectileLocation = tankBarrel->GetSocketTransform(FName("Projectile"), ERelativeTransformSpace::RTS_World);
        AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(projectileBlueprint, projectileLocation, FActorSpawnParameters());
        projectile->LaunchProjectile(launchSpeed);
        
        //TODO: Play Big Shaq BOOM sound
        
        
        lastFireTime = FPlatformTime::Seconds();
    }
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector aimLocation)
{
    aimingComponent->AimAt(aimLocation, launchSpeed);
    
}

void ATank::SetBarrelReference(UTankBarrel* barrelToSet)
{
    aimingComponent->SetBarrelReference(barrelToSet);
    tankBarrel = barrelToSet;
}

void ATank::SetTurretReference(UTankTurret* turretToSet)
{
    aimingComponent->SetTurretReference(turretToSet);
}
