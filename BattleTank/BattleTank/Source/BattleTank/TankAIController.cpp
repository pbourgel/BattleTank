// It's MIT licensed fam

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();

}

void ATankAIController::Tick(float DeltaTime)
{
    
    APawn* playerTankPwn = GetWorld()->GetFirstPlayerController()->GetPawn();
    AITank = GetPawn();
    
    if(!(playerTankPwn && AITank)) { return; }
    
    //TODO: Move towards the player
    MoveToActor(Cast<AActor>(playerTankPwn), AcceptanceRadius, true, true, false);  //TODO: Check radius is in centimeters
        
    AITankAiming = AITank->FindComponentByClass<UTankAimingComponent>();
        
    //Start aiming towards the player
    AITankAiming->AimAt(playerTankPwn->GetActorLocation());
        
    //Fire at player
    //TODO: Fix Firing
    EFiringStatus firingState = AITankAiming->GetFiringState();
    if(firingState == EFiringStatus::Locked)
    {
        AITankAiming->Fire();
    }
}

void ATankAIController::SetPawn(APawn* InPawn)
{
    Super::SetPawn(InPawn);
    
    if(InPawn)
    {
        ATank* PossessedTank = Cast<ATank>(InPawn);
        if(!PossessedTank) { return; }
        
        //Subscribe the local method to the tank's death event
        PossessedTank->TankDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
    }
}

void ATankAIController::OnTankDeath()
{
    //UE_LOG(LogTemp, Warning, TEXT("ATankAIController; In OnTankDeath()"))
    //Would we play death animations/sequences around here?  Maybe
    if(!GetPawn()) { return; }
    GetPawn()->DetachFromControllerPendingDestroy();
}
