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


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


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
        if(UGameplayStatics::SuggestProjectileVelocity(this,
                                  OutLaunchVelocity,
                                  startLocation,
                                  worldSpaceAim,
                                  launchSpeed,
                                  false,
                                  0.0f, //TODO: Find sensible collision radius BOOM
                                  0.0f,
                                  ESuggestProjVelocityTraceOption::Type::DoNotTrace))
        {
            auto aimDirection = OutLaunchVelocity.GetSafeNormal();
            auto tankName = GetOwner()->GetName();
            UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s"), *tankName, *(aimDirection.ToString()));
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
