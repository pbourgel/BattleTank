// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

void UTankBarrel::Elevate(float relativeSpeed)
{
    //Rotate (lerp in Unity-speak) to the new rotation ONLY along the pitch given a max rotation speed and the frame time
    //(wanna keep this frame independent)
    //UE_LOG(LogTemp, Warning, TEXT("In tankBarrel->Elevate() with speed %f"), relativeSpeed)
    
    relativeSpeed = FMath::Clamp<float>(relativeSpeed, -1.0f, 1.0f);
    
    float elevationChange = relativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
    float rawNewElevation = RelativeRotation.Pitch + elevationChange;
    
    // Ah #&@*&^%#!!! I got so used to out parameters I thought this would mutate rawNewElevation.
    //I blame the cold I'm shrugging off as I write this.
    float finalElevation = FMath::Clamp<float>(rawNewElevation, MinElevationDegrees, MaxElevationDegrees);
    
    SetRelativeRotation(FRotator(finalElevation, 0.0, 0.0));
    
}
