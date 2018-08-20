// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

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
//// Called every frame
//void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//    // ...
//}

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
                                  ESuggestProjVelocityTraceOption::Type::DoNotTrace);
        if(bHaveAimSolution)
        {
            auto aimDirection = OutLaunchVelocity.GetSafeNormal();
            auto tankName = GetOwner()->GetName();
            //UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s"), *tankName, *(aimDirection.ToString()));
            MoveBarrelTowards(OutLaunchVelocity);
        }
        else
        {

        }

        
    }
}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* barrelToSet)
{
    tankBarrel = barrelToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector aimDirection)
{

    //Calculate the new rotation from the unit vector stored in OutLaunchVelocity
    FRotator fwdRotator = tankBarrel->GetForwardVector().Rotation();
    FRotator aimRotation = aimDirection.Rotation();
    FRotator deltaRotator = aimRotation - fwdRotator;
    
    UE_LOG(LogTemp, Warning, TEXT("aimRotation: %s"), *(aimRotation.ToString()))
    
    
    
    //Rotate (lerp in Unity-speak) to the new rotation ONLY along the pitch given a max rotation speed and the frame time
    //TODO: Need barrel.cpp first to store rotation limits
    
    //(wanna keep this frame independent)

    
    //Rotate the turret
    
    
    
}
