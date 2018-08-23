// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Kismet/GameplayStatics.h"
#include <cmath>

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


//// Called when the game starts
//void UTankAimingComponent::BeginPlay()
//{
//    Super::BeginPlay();
//
//    // ...
//
//}
//
//
// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // ...
}

void UTankAimingComponent::AimAt(FVector worldSpaceAim, float launchSpeed)
{
    //UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s from %s with launch speed %f"), *(GetOwner()->GetName()), *worldSpaceAim.ToString(), *(tankBarrel->GetComponentLocation().ToString()), launchSpeed);
    
    FVector OutLaunchVelocity;
    
    if(!tankBarrel) { return; }
    else
    {
        FVector startLocation = tankBarrel->GetSocketLocation(FName("Projectile"));
        
        //OutLaunchVelocity = startLocation * launchSpeed;
        
        //Calculate the OutLaunchVelocity
        bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this,
                                  OutLaunchVelocity,
                                  startLocation,
                                  worldSpaceAim,
                                  launchSpeed,
                                  false,
                                  0.0f,
                                  0.0f,
                                  ESuggestProjVelocityTraceOption::Type::DoNotTrace);
        if(bHaveAimSolution)
        {
            auto aimDirection = OutLaunchVelocity.GetSafeNormal();
            auto tankName = GetOwner()->GetName();
            //UE_LOG(LogTemp, Warning, TEXT("Aim solution found"));
            MoveBarrelTowards(OutLaunchVelocity);
        }
        else
        {
            //UE_LOG(LogTemp, Warning, TEXT("Aim solution NOT found"));
        }

        if(!tankTurret) { return; }
        else
        {
            MoveTurretTowards(worldSpaceAim.GetSafeNormal());
        }
    }
    

}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* barrelToSet)
{
    if(!barrelToSet) { return; }
    tankBarrel = barrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* turretToSet)
{
    if(!turretToSet) { return; }
    tankTurret = turretToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector aimDirection)
{

    //Calculate the new rotation from the unit vector stored in OutLaunchVelocity
    FRotator fwdRotator = tankBarrel->GetForwardVector().Rotation();
    FRotator aimRotation = aimDirection.Rotation();
    FRotator deltaRotator = aimRotation - fwdRotator;
    
    //UE_LOG(LogTemp, Warning, TEXT("aimRotation: %s"), *(aimRotation.ToString()))

    tankBarrel->Elevate(deltaRotator.Pitch);
    //tankTurret->TurretRotate(deltaRotator.Yaw);
    
}

void UTankAimingComponent::MoveTurretTowards(FVector aimDirection)
{
    //Rotate the turret
    
    FRotator turretFwd = tankTurret->GetForwardVector().Rotation();
    FRotator turretAimRotation = aimDirection.Rotation();
    FRotator turretDeltaRotator = turretAimRotation - turretFwd;
    
    if(abs(turretDeltaRotator.Yaw) > 180)
    {
        tankTurret->TurretRotate(turretDeltaRotator.Yaw * -1);
    }
    else
    {
        tankTurret->TurretRotate(turretDeltaRotator.Yaw);
    }
    //tankTurret->TurretRotate(turretDeltaRotator.Yaw);
}
