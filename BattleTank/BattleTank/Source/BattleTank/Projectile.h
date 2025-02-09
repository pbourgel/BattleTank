// It's MIT licensed fam

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;
class UStaticMeshComponent;
class UParticleSystemComponent;
class URadialForceComponent;

/*
 * Launches projectiles and related effects.
 */
UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

    void LaunchProjectile(float speed);
    
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, Category = Components, meta = (AllowPrivateAccess = true))
    UStaticMeshComponent* CollisionMesh = nullptr;
    
    UPROPERTY(VisibleAnywhere, Category = Components, meta = (AllowPrivateAccess = true))
    UParticleSystemComponent* LaunchBlast = nullptr;
    
    UPROPERTY(VisibleAnywhere, Category = Components, meta = (AllowPrivateAccess = true))
    UParticleSystemComponent* ImpactBlast = nullptr;

    UPROPERTY(VisibleAnywhere, Category = Components, meta = (AllowPrivateAccess = true))
    URadialForceComponent* ExplosionForce = nullptr;
    
    UPROPERTY(EditDefaultsOnly, Category = Setup)
    float DestroyDelay = 5.0f;
    
    UPROPERTY(EditDefaultsOnly, Category = Setup)
    float baseDamage = 20.0f;
    
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
    
    UProjectileMovementComponent* projectileMovementComponent = nullptr;

    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
    
    void OnTimerExpire();
};
