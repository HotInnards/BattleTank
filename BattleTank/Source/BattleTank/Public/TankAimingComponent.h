// Copyright Buffster Studios Ltd.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Forward declarations
class UTankBarrel;
class UTankTurret;
class AProjectile;

// Enum for aiming state
UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked
};

// Hold barrel properties and required methods
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* Barrel, UTankTurret* Turret);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

	void AimAt(FVector HitLocation);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	UTankAimingComponent* TankAimingComponent = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Reloading;

private:
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	// Sets default values for this component's properties
	UTankAimingComponent();

	void AimToward(FVector AimDirection);

	bool IsBarrelMoving();

	UTankBarrel* Barrel = nullptr;

	UTankTurret* Turret = nullptr;

	double LastFireTime = 0;

	FVector AimDirection;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	TSubclassOf<AProjectile> ProjectileBlueprint;
	// UClass* ProjectileBlueprint; More generic alternative to choose from all available classes

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 5000;
	
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 3;

};
