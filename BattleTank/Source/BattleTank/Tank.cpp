// It's MIT licensed fam

#include "Tank.h"
#include "TankAimingComponent.h"
//#include "TankMovementComponent.h"
#include "TankBarrel.h"
//#include "TankTurret.h"
#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    UE_LOG(LogTemp, Warning, TEXT("DISCONSCIOUS: In Tank Constructor"))
    //No need to protect pointers as added at construction
    //aimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("AimingComponent"));
    
    //movementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("MovementComponent"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
    UE_LOG(LogTemp, Warning, TEXT("DISCONSCIOUS: %s In Tank BeginPlay()"), *(GetName()))

    Super::BeginPlay();     //Needed for BP BeginPlay() to run!

}

void ATank::Fire()
{
    bool bIsReloaded = (FPlatformTime::Seconds() - lastFireTime) > reloadTimeInSeconds;
    
    //ensure fails here
    if(!ensure(tankBarrel)) { return; }
    
    if(bIsReloaded) {

        //Spawn a projectile at the socket location
        FTransform projectileLocation = tankBarrel->GetSocketTransform(FName("Projectile"), ERelativeTransformSpace::RTS_World);
        AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(projectileBlueprint, projectileLocation, FActorSpawnParameters());
        projectile->LaunchProjectile(launchSpeed);
        
        //TODO: Play Big Shaq BOOM sound
        
        
        lastFireTime = FPlatformTime::Seconds();
    }
}

//// Called to bind functionality to input
//void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//    Super::SetupPlayerInputComponent(PlayerInputComponent);
//
//}

void ATank::AimAt(FVector aimLocation)
{   //ensure fails here
    if(!ensure(aimingComponent)) { return; }
    aimingComponent->AimAt(aimLocation, launchSpeed);
    
}

