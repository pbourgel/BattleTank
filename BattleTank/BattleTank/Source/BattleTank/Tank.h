// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"  //This must be the last include!

//Forward declarations
class UTankBarrel;

/*
 * Handles firing and calls aiming functions on UTankAimingComponent.
 * This class keeps track of variables such as projectile launch speed and time to reload.
 */
UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
