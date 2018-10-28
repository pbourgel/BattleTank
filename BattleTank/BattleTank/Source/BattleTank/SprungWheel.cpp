// It's MIT fam

#include "SprungWheel.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    Spring = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Spring"));
    //Spring->SetupAttachment(Mass);
    SetRootComponent(Spring);
    
    Mass = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mass"));
    Mass->SetupAttachment(Spring);
    
    Wheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wheel"));
    Wheel->SetupAttachment(Spring);

    //Spring->ComponentName1.ComponentName = FName(Mass->GetName());
    //Spring->ComponentName2.ComponentName = Wheel->GetName();
    
//    //Set up stiffness and damping, but we don't want max force applied by the spring
//    Spring->SetLinearDriveParams(5000.0f, 2000.0f, 0.0f);
//    
//    //Make sure we're constricting this to the Z axis
//    Spring->SetLinearPositionDrive(false, false, true);
//    Spring->SetLinearVelocityDrive(false, false, true);
//    
//    //Keep the spring at the default position
//    Spring->SetLinearPositionTarget(FVector(0.0f, 0.0f, 0.0f));
//    Spring->SetLinearVelocityTarget(FVector(0.0f, 0.0f, 0.0f));
//    
//    //No rotation weirdness
//    Spring->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0.0f);
//    Spring->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0.0f);
//    Spring->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 0.0f);

}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
    auto returnedActor = GetAttachParentActor();
    if(returnedActor)
    {
        UE_LOG(LogTemp, Warning, TEXT("returnedActor not null: %s"), *GetAttachParentActor()->GetName())
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Null returnedActor"))
    }
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

