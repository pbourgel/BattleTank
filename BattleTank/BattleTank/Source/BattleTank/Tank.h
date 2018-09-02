// It's MIT licensed fam

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"  //This must be the last include!

//Forward declarations
class UTankBarrel;

//Delegate declarations
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDeathDelegate);


/*
 * Handles firing and calls aiming functions on UTankAimingComponent.
 * This class keeps track of variables such as projectile launch speed and time to reload.
 */
UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:

    //Called by the engine when actor damage is dealt
    virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
    
    //Returns current health as a percentage of starting health between 0 and 1
    UFUNCTION(BlueprintPure, Category = Health)
    float GetHealthPercent() const;
    
    FTankDeathDelegate TankDeath;
    
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    
private:
    
    // Sets default values for this pawn's properties
    ATank();
    
    UPROPERTY(EditDefaultsOnly, Category = Stats)
    int32 startingTankHealth = 100.0f;
    
    UPROPERTY(VisibleAnywhere, Category = Stats)
    int32 currentHealth = 100.0f;
    
    FTankDeathDelegate TankDestructionDelegate;
};
