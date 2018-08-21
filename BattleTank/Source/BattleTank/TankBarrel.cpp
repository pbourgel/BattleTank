// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

void UTankBarrel::Elevate(float elevateSpeed)
{
    //Rotate (lerp in Unity-speak) to the new rotation ONLY along the pitch given a max rotation speed and the frame time
    //(wanna keep this frame independent)
    UE_LOG(LogTemp, Warning, TEXT("In tankBarrel->Elevate() with speed %f"), elevateSpeed)
}
