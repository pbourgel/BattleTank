// It's MIT licensed fam
#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;
    
    CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
    SetRootComponent(CollisionMesh);
    CollisionMesh->SetNotifyRigidBodyCollision(true);
    CollisionMesh->SetVisibility(false);
    
    LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
    LaunchBlast->SetupAttachment(CollisionMesh);
    //LaunchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
    
    projectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
    projectileMovementComponent->bAutoActivate = false;
    
    ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));
    ImpactBlast->SetupAttachment(CollisionMesh);
    ImpactBlast->bAutoActivate = false;
    
    ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Force"));
    ExplosionForce->SetupAttachment(CollisionMesh);
    
    
}

//When the projectile hits, we want to
//  1. Stop the smoke trail (launch blast)
//  2. Make the ting go BOOM (activate the impact blast)
//  3. Push the tank
//  4. Get rid of the round  (but we have to set a new root component before we get rid of the mesh)
void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
    UE_LOG(LogTemp, Warning, TEXT("In ObHit()"))
    LaunchBlast->Deactivate();
    ImpactBlast->Activate();
    ExplosionForce->FireImpulse();
    
    SetRootComponent(ImpactBlast);
    CollisionMesh->DestroyComponent();
    
    //We're setting up a simple timer to destroy the projectile after some time so it doesn't take up memory
    FTimerHandle timerHandle;
    
    GetWorld()->GetTimerManager().SetTimer(timerHandle, this, &AProjectile::OnTimerExpire, DestroyDelay, false);
}

void AProjectile::OnTimerExpire()
{
    Destroy();
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
    CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::LaunchProjectile(float speed)
{
    //UE_LOG(LogTemp, Warning, TEXT("In LaunchProjectile() with speed %f"), speed)
    projectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * speed);
    projectileMovementComponent->Activate();
}
