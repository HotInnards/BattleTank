// Copyright Buffster Studios Ltd.


#include "TankAIController.h"
#include "Tank.h"
#include "Engine/World.h"
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
	auto ControlledTank = Cast<ATank>(GetPawn());

	if (!ensure(TankAimingComponent)) { return; }
	if (ensure(PlayerTank)) {
		// Move towards the player
		MoveToActor(PlayerTank, AcceptanceRadius); // TODO check radius units

		// Aim towards the player
		TankAimingComponent->AimAt(PlayerTank->GetActorLocation());

		// Fire if ready
		ControlledTank->Fire();
	}
}
