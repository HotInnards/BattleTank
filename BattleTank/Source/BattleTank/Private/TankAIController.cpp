// Copyright Buffster Studios Ltd.


#include "TankAIController.h"
#include "Engine/World.h"
#include "Tank.h" // required to implement OnDeath function call
#include "TankAimingComponent.h"
// Depends on the movement component via pathfinding system

// Called when the game starts or when spawned
void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	TankAimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();

	if (!ensure(PlayerTank && ControlledTank && TankAimingComponent)) { return; }
	
	// Move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius); // TODO check radius units

	// Aim towards the player
	TankAimingComponent->AimAt(PlayerTank->GetActorLocation());

	// Fire if ready
	if (TankAimingComponent->GetFiringState() == EFiringState::Locked)
	{
		TankAimingComponent->Fire();
	}
}

void ATankAIController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		// Subscribe local method to the tank's death event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
	}
}

void ATankAIController::OnPossessedTankDeath()
{
	if (!GetPawn()) { return; }
	GetPawn()->DetachFromControllerPendingDestroy();
}
