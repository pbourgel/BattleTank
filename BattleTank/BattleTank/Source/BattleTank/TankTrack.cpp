// It's MIT licensed fam

#include "TankTrack.h"
#include "Kismet/GameplayStatics.h"
#include "SprungWheel.h"

UTankTrack::UTankTrack()
{
    
}

void UTankTrack::BeginPlay()
{
    Super::BeginPlay();
    PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::SetThrottle(float throttleValue)
{
    float currentThrottle = FMath::Clamp<float>(throttleValue, -1.0f, 1.0f);
    DriveTrack(currentThrottle);
//    currentThrottle = 0.0f;
}

TArray<ASprungWheel*> UTankTrack::GetWheels() const
{
    //TArray<ASprungWheel*> WheelArr;
    TArray<USceneComponent*> SpawnerArr;
    TArray<ASprungWheel*> WheelArr;

    //GetChildrenComponents(true, WheelArr);
    //Get Spawn Point components
    //get the wheel actor that is spawned
    return WheelArr;
}

void UTankTrack::DriveTrack(float currentThrottle)
{
    UE_LOG(LogTemp, Warning, TEXT("%s: In SetThrottle: throttleValue %f"), *(GetName()), currentThrottle)
    
    float ForceApplied = currentThrottle * TrackMaxDrivingForce;
    TArray<ASprungWheel*> Wheels = GetWheels();
    float ForcePerWheel = ForceApplied / Wheels.Num();
    for(ASprungWheel* Wheel : Wheels)
    {
        Wheel->ApplyDrivingForce(ForcePerWheel);
    }
}

void  UTankTrack::OnRegister()
{
    Super::OnRegister();
    PrimaryComponentTick.bCanEverTick = true;
}
