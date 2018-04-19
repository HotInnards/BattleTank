// Copyright Buffster Studios Ltd.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// Forward declarations
class UTankAimingComponent;
class UTankMovementComponent;
class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	UTankAimingComponent* TankAimingComponent = nullptr;
	
	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	UTankMovementComponent* TankMovementComponent = nullptr;

private:
	// Sets default values for this pawn's properties
	ATank();

	// Local barrel reference for spawning projectile
	UTankBarrel* Barrel = nullptr; // TODO remove

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;
	// UClass* ProjectileBlueprint; More generic alternative to choose from all available classes

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 5000;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 3;

	double LastFireTime = 0;

};
