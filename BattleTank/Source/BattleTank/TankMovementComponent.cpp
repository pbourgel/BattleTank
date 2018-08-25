// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"


void UTankMovementComponent::IntendMoveForward(float Throw)
{
    //UE_LOG(LogTemp, Warning, TEXT("IntendMoveForward: Throw = %f"), Throw)
        if(!LeftTrack || !RightTrack) { return; }  //MAYBE TODO: Report an error
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(Throw);
    //TODO: Prevent double-speed due to dual control use
    
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
    //UE_LOG(LogTemp, Warning, TEXT("IntendMoveForward: Throw = %f"), Throw)
        if(!LeftTrack || !RightTrack) { return; }  //MAYBE TODO: Report an error
    LeftTrack->SetThrottle(-Throw);
    RightTrack->SetThrottle(Throw);
    //TODO: Prevent double-speed due to dual control use
    
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
    //No need to call Super 'cause we're overriding errythang
    //UE_LOG(LogTemp, Warning, TEXT("%s in RequestDirectMove() with MoveVelocity %s"), *(GetName()), *(MoveVelocity.ToString()))
    
    FVector AIForwardIntention = MoveVelocity.GetSafeNormal();
    FVector TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
    
    IntendMoveForward(FVector::DotProduct(TankForward, AIForwardIntention));
    
    IntendTurnRight(FVector::CrossProduct(TankForward, AIForwardIntention).Z);
    
}

void UTankMovementComponent::Initialize(UTankTrack* leftTrackToSet, UTankTrack* rightTrackToSet)           //Spelt with a z because MURRICA
{

    
    LeftTrack = leftTrackToSet;
    RightTrack = rightTrackToSet;
}

