// It's MIT licensed fam

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"
#include <cmath>

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
    Super::BeginPlay();

    // ...

    tankBarrel = GetOwner()->FindComponentByClass<UTankBarrel>();
    
    //Added so that first fire is after initial reload
    lastFireTime = FPlatformTime::Seconds();
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // ...
    if(bulletsLeft <= 0)
    {
        firingState = EFiringStatus::ManGotNoBullets;
    }
    else if((FPlatformTime::Seconds() - lastFireTime) < reloadTimeInSeconds)
    {
        
        //UE_LOG(LogTemp, Warning, TEXT("Time since last fire: %f"), FPlatformTime::Seconds() - lastFireTime)
        firingState = EFiringStatus::Reloading;
    }
    else if(IsBarrelMoving() == EBarrelMoving::Moving)
    {
        firingState = EFiringStatus::Aiming;
    }
    else if(IsBarrelMoving() == EBarrelMoving::DontAskMeICantEvenLookThroughTheBarrelPointerRightNowMate)
    {
        UE_LOG(LogTemp, Error, TEXT("BARREL POINTER NOT FOUND!!!"))
    }
    else
    {
        firingState = EFiringStatus::Locked;
    }
    //TODO handle aiming and locked states
    
}

EFiringStatus UTankAimingComponent::GetFiringState() const { return firingState; }

EBarrelMoving UTankAimingComponent::IsBarrelMoving()
{
    if(!ensure(tankBarrel)) { return EBarrelMoving::DontAskMeICantEvenLookThroughTheBarrelPointerRightNowMate; }
    FVector barrelFwdVector = tankBarrel->GetForwardVector();
    if(barrelFwdVector.Equals(aimDirection, 0.01f))
    {
        return EBarrelMoving::NotMoving;
    }
    else
    {
        return EBarrelMoving::Moving;
    }
}

void UTankAimingComponent::AimAt(FVector worldSpaceAim)
{
    
    FVector OutLaunchVelocity;
    
    if(!ensure(tankBarrel)) { return; }
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
            aimDirection = OutLaunchVelocity.GetSafeNormal();
            auto tankName = GetOwner()->GetName();
            //UE_LOG(LogTemp, Warning, TEXT("Aim solution found"));
            MoveBarrelTowards(aimDirection);

        }
        else
        {
            //UE_LOG(LogTemp, Warning, TEXT("Aim solution NOT found"));
        }


    }
    

}

void UTankAimingComponent::Initialize(UTankTurret* turretToSet, UTankBarrel* barrelToSet)
{
    if(!ensure(barrelToSet)) { return; }
    tankBarrel = barrelToSet;
    
    if(!ensure(turretToSet)) { return; }
    tankTurret = turretToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector aimDirection)
{
    
    if(!ensure(tankBarrel && tankTurret)) { return; }
    //Calculate the new rotation from the unit vector stored in OutLaunchVelocity
    FRotator fwdRotator = tankBarrel->GetForwardVector().Rotation();
    FRotator aimRotation = aimDirection.Rotation();
    FRotator deltaRotator = aimRotation - fwdRotator;
    
    //UE_LOG(LogTemp, Warning, TEXT("aimRotation: %s"), *(aimRotation.ToString()))

    tankBarrel->Elevate(deltaRotator.Pitch);
    
    if (FMath::Abs(deltaRotator.Yaw) < 180)
    {
        tankTurret->TurretRotate(deltaRotator.Yaw);
    }
    else // Avoid going the long-way round
    {
        tankTurret->TurretRotate(-deltaRotator.Yaw);
    }
    //tankTurret->TurretRotate(deltaRotator.Yaw);
    
}

void UTankAimingComponent::MoveTurretTowards(FVector aimDirection)
{
    //Rotate the turret
    //UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s from %s"), *(GetOwner()->GetName()), *aimDirection.ToString(), *(tankBarrel->GetComponentLocation().ToString()));

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
}

void UTankAimingComponent::Fire()
{
    //ensure fails here
    
    if(firingState == EFiringStatus::Locked
       || firingState == EFiringStatus::Aiming) {
        if(!ensure(tankBarrel)) { return; }
        if(!ensure(projectileBlueprint)) { return; }
        //Spawn a projectile at the socket location
        FTransform projectileLocation = tankBarrel->GetSocketTransform(FName("Projectile"), ERelativeTransformSpace::RTS_World);
        AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(projectileBlueprint, projectileLocation, FActorSpawnParameters());
        projectile->LaunchProjectile(launchSpeed);
        
        //TODO: Play Big Shaq BOOM sound
        
        lastFireTime = FPlatformTime::Seconds();
        bulletsLeft--;
    }
}

int32 UTankAimingComponent::GetBulletsLeft() const
{
    return bulletsLeft;
}

