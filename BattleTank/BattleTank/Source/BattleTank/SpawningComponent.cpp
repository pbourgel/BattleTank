// It's MIT fam

#include "SpawningComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
USpawningComponent::USpawningComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USpawningComponent::BeginPlay()
{
	Super::BeginPlay();
    AActor* spawnedWheel = GetWorld()->SpawnActorDeferred<AActor>(WheelAttachment, GetComponentTransform());
    if(spawnedWheel != nullptr)
    {
        spawnedWheel->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("In SpawningComponent, unable to spawn wheel"))
        return;
    }
	// ...
    UGameplayStatics::FinishSpawningActor(spawnedWheel, GetComponentTransform());
}


// Called every frame
void USpawningComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

