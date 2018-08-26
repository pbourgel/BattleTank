// It's MIT licensed fam

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * Represents the barrel and its elevation logic called by TankAimingComponent.
 */
UCLASS(meta=(BlueprintSpawnableComponent), hidecategories = ("Collision"))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
    //-1 is max downward movement, +1 is max upwards
    void Elevate(float relativeSpeed);    
    
private:
    UPROPERTY(EditAnywhere, Category = Setup)
    float MaxDegreesPerSecond = 10.0f;
    
    UPROPERTY(EditDefaultsOnly, Category = Setup)
    float MaxElevationDegrees = 40.0f;
    
    UPROPERTY(EditDefaultsOnly, Category = Setup)
    float MinElevationDegrees = 0.0f;
    
};
