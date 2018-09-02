// It's MIT licensed fam

#include "Tank.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
    Super::BeginPlay();     //Needed for BP BeginPlay() to run!
    startingTankHealth = currentHealth;
}


float ATank::GetHealthPercent() const
{
    return (float)currentHealth / (float)startingTankHealth;
}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
    int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
    int32 DamageToApply = FMath::Clamp<int32>(DamagePoints, 0.0f, currentHealth);
    currentHealth -= DamageToApply;
    if(currentHealth <= 0) { UE_LOG(LogTemp, Warning, TEXT("Tank is dead: Return of Ganon")) }
    UE_LOG(LogTemp, Warning, TEXT("OW!!! Damage amount = %f  Damage to apply = %i"), DamageAmount, DamageToApply)
    
    return DamageToApply;
}
