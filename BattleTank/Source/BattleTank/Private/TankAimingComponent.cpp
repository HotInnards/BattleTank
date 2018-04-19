// Copyright Buffster Studios Ltd.

#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	LastFireTime = GetWorld()->GetTimeSeconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	if (bool IsReloaded = (GetWorld()->GetTimeSeconds() - LastFireTime) > ReloadTimeInSeconds)
	{
		FiringState = EFiringState::Reloading;
	}

	// TODO handle aiming and locked states
}

// Sets default values
void UTankAimingComponent::Initialise(UTankBarrel * Barrel, UTankTurret * Turret)
{
	if (!ensure(Barrel && Turret)) { return; }
	this->Barrel = Barrel;
	this->Turret = Turret;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel && Turret)) { return; }
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if (bHaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		AimToward(AimDirection);
	}
}

void UTankAimingComponent::AimToward(FVector AimDirection)
{
	if (!ensure(Barrel && Turret)) { return; }
	// Work out difference between current barrel elevation / turret rotation and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);
}


void UTankAimingComponent::Fire()
{


	if (FiringState != EFiringState::Reloading)
	{
		// Spawn a projectile at the socket location on the barrel
		if (!ensure(Barrel && ProjectileBlueprint)) { return; }
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketTransform(FName("Projectile"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();
	}
}
