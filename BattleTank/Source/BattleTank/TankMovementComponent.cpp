// It's MIT licensed fam

#include "TankMovementComponent.h"
#include "TankTrack.h"


void UTankMovementComponent::IntendMoveForward(float Throw)
{
    //UE_LOG(LogTemp, Warning, TEXT("IntendMoveForward: Throw = %f"), Throw)
        if(!LeftTrack || !RightTrack) { return; }  //MAYBE TODO: Report an error
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
    //UE_LOG(LogTemp, Warning, TEXT("IntendMoveForward: Throw = %f"), Throw)
        if(!LeftTrack || !RightTrack) { return; }  //MAYBE TODO: Report an error
    LeftTrack->SetThrottle(-Throw);
    RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
    //No need to call Super 'cause we're overriding errythang
    //UE_LOG(LogTemp, Warning, TEXT("%s in RequestDirectMove() with MoveVelocity %s"), *(GetName()), *(MoveVelocity.ToString()))
    
    FVector AIForwardIntention = MoveVelocity.GetSafeNormal();
    FVector TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
    
    float forwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
    float rightThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
    
    IntendMoveForward(forwardThrow);
    IntendTurnRight(rightThrow);
    //UE_LOG(LogTemp, Warning, TEXT("Forward: %f  Right: %f"), forwardThrow, rightThrow)
}

void UTankMovementComponent::Initialize(UTankTrack* leftTrackToSet, UTankTrack* rightTrackToSet)           //Spelt with a z because MURRICA
{
    LeftTrack = leftTrackToSet;
    RightTrack = rightTrackToSet;
}

