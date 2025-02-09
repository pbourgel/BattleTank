// It's MIT fam

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SpawningComponent.generated.h"

class USphereComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API USpawningComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpawningComponent();

    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    
    UPROPERTY(EditDefaultsOnly, Category = PhysicsAttachment)
    TSubclassOf<AActor> WheelAttachment;
    
    AActor* GetSpawnedWheel() const;
    
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
    
private:
    
    UPROPERTY()
    AActor* spawnedWheel;
    
};
