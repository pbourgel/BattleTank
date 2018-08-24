// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

void UTankTrack::SetThrottle(float throttleValue)
{
    //UE_LOG(LogTemp, Warning, TEXT("%s: In SetThrottle: throttleValue %f"), *(GetName()), throttleValue)
    
    //TODO?  The tutorial is gonna clamp this here.  I've already clamped it in BP, but hey, might as well when the get around to it.
    //Gotta sanitize those inputs
    
    FVector ForceApplied = GetForwardVector() * throttleValue * TrackMaxDrivingForce;
    FVector ForceLocation = GetComponentLocation();
    USceneComponent* TankRoot = GetOwner()->GetRootComponent();
    Cast<UPrimitiveComponent>(TankRoot)->AddForceAtLocation(ForceApplied, ForceLocation);
}


