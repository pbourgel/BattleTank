// It's MIT fam

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SprungWheel.generated.h"

class UStaticMeshComponent;
class UPhysicsConstraintComponent;
class USphereComponent;

UCLASS()
class BATTLETANK_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASprungWheel();
    
    // Called every frame
    virtual void Tick(float DeltaTime) override;
    
    void ApplyDrivingForce(float ForceMagnitude);
    
    void ApplyForce();
    
    USphereComponent* GetWheel() const;
    
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    
private:
    
    UPROPERTY(VisibleAnywhere, Category = "Components")
    USphereComponent* Wheel;
    
    UPROPERTY(VisibleAnywhere, Category = "Components")
    UPhysicsConstraintComponent* Spring;

    void SetupConstraints();
    
    UPROPERTY(VisibleAnywhere, Category = "Components")
    UPhysicsConstraintComponent* AxleWheelConstraint;
    
    UPROPERTY(VisibleAnywhere, Category = "Components")
    USphereComponent* Axle;
    
    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
    
    float TotalForceMagnitudeThisFrame;
    
};
