// It's MIT licensed fam

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Math/Vector.h"
#include "Tank.h"

/*
 * Responsible for helping the player aim
 */

void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();
    PlayerTank = GetPawn();
    if(!ensure(PlayerTank)) { return; }
    
    aimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    
    if(!ensure(aimingComponent)) { return; }
    else { FoundAimingComponent(aimingComponent);  }
}

void ATankPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    //UE_LOG(LogTemp, Warning, TEXT("In Tick() in TankPlayerController"));
    AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
    if(!GetPawn()) { return; }
    FVector HitLocation;

    //UE_LOG(LogTemp, Warning, TEXT("Hitlocation: %s"),*HitLocation.ToString());
    
    //Get world location of linetrace through crosshair (in Unityspeak this is a ScreenToPointRay raycast at the crosshair)
    bool bGotHitLocation = GetSightRayHitLocation(HitLocation); //Side-effect: Performs raytrace and stores location of object hit in HitLocation
    //UE_LOG(LogTemp, Warning, TEXT("%i"), bGotHitLocation)
    if(bGotHitLocation)
    {
        //If it hits the landscape
        //Tell aiming component to aim at this point
        aimingComponent->AimAt(HitLocation);
    }

    
}

bool ATankPlayerController::GetLookDirection(FVector2D screenLocation, FVector& lookDirection) const
{
    FVector worldLocation;
    //(in Unityspeak this is ScreenToPointRay, where the ray is coming from the crosshair)
    //Find the crosshair position
    //UE_LOG(LogTemp, Warning, TEXT("ScreenLocation: %s"),*screenLocation.ToString())
    
    //"De-project" the screen position of the crosshair to a world direction
    if(DeprojectScreenPositionToWorld(
                                      screenLocation.X,
                                      screenLocation.Y,
                                      worldLocation,
                                      lookDirection))
    {
        return true;
    }
    else
    {
        return false;
    }
}

//Linetrace through the given lookDirection and return the coordinates of the first thing we hit
bool ATankPlayerController::GetLookVectorHitLocation(FVector& hitLocation, FVector lookDirection) const
{
    FHitResult traceHit;
    FVector startLocation = PlayerCameraManager->GetCameraLocation();
    //FCollisionQueryParams TraceParameters = FCollisionQueryParams(FName(TEXT("")),false, GetOwner());
    if(GetWorld()->LineTraceSingleByChannel(traceHit,
                                            startLocation,
                                            startLocation + (lookDirection * lineTraceRange),
                                            ECollisionChannel::ECC_Camera))
    {
        hitLocation = traceHit.Location;
        return true;
    }
    else
    {
        return false;
    }
    
}

//Get world location of linetrace through crosshair, return true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
    FVector lookDirection;
    FHitResult traceHit;
    //(in Unityspeak this is a ScreenToPointRay raycast at the crosshair)
    //Find the crosshair position
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);
    FVector2D screenLocation = FVector2D(ViewportSizeX*CrossHairXLocation, ViewportSizeY*CrossHairYLocation);

    //UE_LOG(LogTemp, Warning, TEXT("ScreenLocation: %s"),*screenLocation.ToString())
    
    //"De-project" the screen position of the crosshair to a world direction
    if(GetLookDirection(screenLocation, lookDirection))
    {        
        //UE_LOG(LogTemp, Warning, TEXT("Found WorldDirection: %s"),*lookDirection.ToString())
        //Line-trace along that look direction and see what we hit up to a maximum range
        
        return GetLookVectorHitLocation(OutHitLocation, lookDirection);

    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("TankPlayerController: Couldn't deproject screen position to world"))
        return false;
    }
    
}

void ATankPlayerController::SetPawn(APawn* InPawn)
{
    Super::SetPawn(InPawn);
    
    if(InPawn)
    {
        ATank* PossessedTank = Cast<ATank>(InPawn);
        if(!ensure(PossessedTank)) { return; }
        
        //Subscribe the local method to the tank's death event
        PossessedTank->TankDeath.AddUniqueDynamic(this, &ATankPlayerController::OnTankDeath);
    }
}

void ATankPlayerController::OnTankDeath()
{
    //UE_LOG(LogTemp, Warning, TEXT("ATankPlayerController; In OnTankDeath()"))
    //Would we play death animations/sequences around here?  Maybe
    StartSpectatingOnly();
}

