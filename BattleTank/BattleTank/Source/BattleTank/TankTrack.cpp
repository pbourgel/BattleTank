// It's MIT licensed fam

#include "TankTrack.h"
#include "Kismet/GameplayStatics.h"
#include "SprungWheel.h"
#include "SpawningComponent.h"

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
    TArray<ASprungWheel*> WheelArr;
    TArray<USceneComponent*> ChildrenComps;
    
    GetChildrenComponents(true, ChildrenComps);
    
    for(USceneComponent* childComp : ChildrenComps)
    {
        USpawningComponent* spawnComp = Cast<USpawningComponent>(childComp);
        if(spawnComp)
        {
            AActor* wheelActor = spawnComp->GetSpawnedWheel();
            ASprungWheel* wheelToAdd = Cast<ASprungWheel>(wheelActor);
            if(wheelToAdd)
            {
                WheelArr.Add(wheelToAdd);
            }
        }
        else
        {
            continue;
        }
    }
    return WheelArr;
}

void UTankTrack::DriveTrack(float currentThrottle)
{
    //UE_LOG(LogTemp, Warning, TEXT("%s: In SetThrottle: throttleValue %f"), *(GetName()), currentThrottle)
    
    float ForceApplied = currentThrottle * TrackMaxDrivingForce;
    TArray<ASprungWheel*> Wheels = GetWheels();
    float ForcePerWheel = ForceApplied / Wheels.Num();
    for(ASprungWheel* Wheel : Wheels)
    {
        Wheel->ApplyDrivingForce(ForcePerWheel);
    }
}

void UTankTrack::OnRegister()
{
    Super::OnRegister();
    PrimaryComponentTick.bCanEverTick = true;
}
