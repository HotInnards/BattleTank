// Copyright Buffster Studios Ltd.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

// Forward declarations
class UTankAimingComponent;

/**
 * This class handles the AI tank behaviour
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

protected:
	UTankAimingComponent* TankAimingComponent = nullptr;

	// How close can AI tank get to the player
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float AcceptanceRadius = 5000; // Default is 50m

private:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SetPawn(APawn* InPawn) override;

	UFUNCTION()
	void OnPossessedTankDeath();

};
