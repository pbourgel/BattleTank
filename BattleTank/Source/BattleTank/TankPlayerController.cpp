// It's MIT licensed fam

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "Math/Vector.h"

/*
 * Responsible for helping the player aim
 */

void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();
    PlayerTank = GetControlledTank();
//    if(PlayerTank != nullptr)
//    {
//        UE_LOG(LogTemp, Warning, TEXT("TankPlayerController: GetControlledTank() possessing %s"), *(PlayerTank->GetName()));
//    }
//    else
//    {
//        UE_LOG(LogTemp, Error, TEXT("TankPlayerController not possessing a tank"));
//    }                                                         //My inner Unity programmer is roaring right now
    UTankAimingComponent* aimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
    if(aimingComponent) { FoundAimingComponent(aimingComponent); }
    else { UE_LOG(LogTemp, Error, TEXT("Aiming component not found")) }
}

void ATankPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    //UE_LOG(LogTemp, Warning, TEXT("In Tick() in TankPlayerController"));
    AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
    APawn* pwn = GetPawn();
    if(!pwn) { return nullptr; }
    return Cast<ATank>(pwn);
}

void ATankPlayerController::AimTowardsCrosshair()
{
    //We aren't aiming anything if we haven't possessed a tank
    if(!GetControlledTank()) return;
    
    FVector HitLocation;

    //UE_LOG(LogTemp, Warning, TEXT("Hitlocation: %s"),*HitLocation.ToString());
    
    //Get world location of linetrace through crosshair (in Unityspeak this is a ScreenToPointRay raycast at the crosshair)
    if(GetSightRayHitLocation(HitLocation)) //Side-effect: Performs raytrace and stores location of object hit in HitLocation
    {
        //If it hits the landscape
        //Tell controlled tank to aim at this point
        GetControlledTank()->AimAt(HitLocation);
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
                                            ECollisionChannel::ECC_Visibility))
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
        
        if(GetLookVectorHitLocation(OutHitLocation, lookDirection))
        {
            //UE_LOG(LogTemp, Warning, TEXT("LookDirectionHit: %s"),*OutHitLocation.ToString())
        }
        
        //if we did hit something, return true
        return true;
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("TankPlayerController: Couldn't deproject screen position to world"))
        return false;
    }
    
}
