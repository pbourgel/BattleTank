// It's MIT fam

#include "SprungWheel.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"


// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    Spring = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Spring"));
    //Spring->SetupAttachment(Mass);
    SetRootComponent(Spring);

    Axle = CreateDefaultSubobject<USphereComponent>(FName("Axle"));
    Axle->SetupAttachment(Spring);
    
    AxleWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Axle - Wheel Constraint"));
    AxleWheelConstraint->SetupAttachment(Axle);
    
    Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
    Wheel->SetupAttachment(Axle);
    
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

void ASprungWheel::SetupConstraints()
{
    auto returnedActor = GetAttachParentActor();
    if(returnedActor)
    {
        //UE_LOG(LogTemp, Warning, TEXT("returnedActor not null: %s"), *GetAttachParentActor()->GetName())
        UPrimitiveComponent* bodyComponent = Cast<UPrimitiveComponent>(returnedActor->GetRootComponent());
        if(bodyComponent == nullptr)
        {
            UE_LOG(LogTemp, Error, TEXT("Can't find component for SprungWheel to attach to"))
            return;
        }
        else
        {
            Spring->SetConstrainedComponents(
                                             bodyComponent,
                                             /*returnedActor->GetName()*/ NAME_None,
                                             Axle,
                                             /*Wheel->GetName()*/ NAME_None);
            
            AxleWheelConstraint->SetConstrainedComponents(Axle, NAME_None, Wheel, NAME_None);
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Null returnedActor"))
        return;
    }
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
    SetupConstraints();
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASprungWheel::ApplyDrivingForce(float ForceMagnitude)
{
    Wheel->AddForce((Axle->GetForwardVector() * ForceMagnitude));
}

USphereComponent* ASprungWheel::GetWheel() const
{
    return Wheel;
}
