// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"

void UTankTurret::TurretRotate(float relativeSpeed)
{
    //Rotate (lerp in Unity-speak) to the new rotation ONLY along the yaw given a max rotation speed and the frame time
    //(wanna keep this frame independent)
    
    relativeSpeed = FMath::Clamp<float>(relativeSpeed, -1.0f, 1.0f);
    
    float rotationChange = relativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
    float NewRotation = RelativeRotation.Yaw + rotationChange;
    
    // Still have a cold, but I understand the code now :P
    //float finalRotation = FMath::Clamp<float>(rawNewRotation, MinRotationDegrees, MaxRotationDegrees);
    //UE_LOG(LogTemp, Warning, TEXT("In tankTurret->TurretRotate() with speed %f"), relativeSpeed)
    SetRelativeRotation(FRotator(0.0, NewRotation, 0.0));
    
}



