// It's MIT licensed fam

#include "TankTrack.h"
#include "Kismet/GameplayStatics.h"

UTankTrack::UTankTrack()
{
    
}

void UTankTrack::BeginPlay()
{
    Super::BeginPlay();
    PrimaryComponentTick.bCanEverTick = false;
    OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::SetThrottle(float throttleValue)
{
    currentThrottle = FMath::Clamp<float>(currentThrottle + throttleValue, -1.0f, 1.0f);
//    DriveTrack();
//    currentThrottle = 0.0f;
}

void UTankTrack::DriveTrack()
{
    UE_LOG(LogTemp, Warning, TEXT("%s: In SetThrottle: throttleValue %f"), *(GetName()), currentThrottle)
    
    //TODO?  The tutorial is gonna clamp this here.  I've already clamped it in BP, but hey, might as well when the get around to it.
    //Gotta sanitize those inputs
    
    FVector ForceApplied = GetForwardVector() * currentThrottle * TrackMaxDrivingForce;
    FVector ForceLocation = GetComponentLocation();
    USceneComponent* TankRoot = GetOwner()->GetRootComponent();
    Cast<UPrimitiveComponent>(TankRoot)->AddForceAtLocation(ForceApplied, ForceLocation);
}

void  UTankTrack::OnRegister()
{
    Super::OnRegister();
    PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
    //UE_LOG(LogTemp, Warning, TEXT("%f: In OnHit event"), UGameplayStatics::GetRealTimeSeconds(GetWorld()))
    //Drive the tracks
    //Apply a sideways force
    DriveTrack();
    ApplySidewaysForce();
    currentThrottle = 0;
}

void UTankTrack::ApplySidewaysForce()
{
    //UE_LOG(LogTemp, Warning, TEXT("In UTankTack::TickComponent"))
    
    //Calculate slippage speed (sideways component of the speed, use a cross product for that)
    float slippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());
    
    float DeltaTime = GetWorld()->GetDeltaSeconds();
    
    //Work out required acceleration this frame to correct (divide by deltaTime)
    FVector appliedAcceleration = -slippageSpeed / DeltaTime * GetRightVector();
    
    //Calculate and apply sideways force (F = m * a)
    UStaticMeshComponent* tankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
    float tankMass = tankRoot->GetMass();                     //Divide by 2 since two tracks
    tankRoot->AddForce((tankMass * appliedAcceleration) / 2.0f);
}
