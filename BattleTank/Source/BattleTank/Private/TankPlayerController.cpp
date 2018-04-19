// Copyright Buffster Studios Ltd.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Components/PrimitiveComponent.h"
#include "Tank.h"
#include "TankAimingComponent.h"

// Called when the game starts or when spawned
void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ATank* ControlledTank = GetControlledTank();
	UTankAimingComponent* AimingComponent = nullptr;
	
	if (ensure(ControlledTank)) {
		AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	}

	if (ensure(AimingComponent)) {
		FoundAimingComponent(AimingComponent);
	} 
}

// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrossHair();

}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());

}

void ATankPlayerController::AimTowardsCrossHair()
{
	if (!ensure(GetControlledTank())) { return; }
	FVector HitLocation; // Out parameter

	if (GetSightRayHitLocation(HitLocation)) { // Has "side-effect", is going to line trace
		// UE_LOG(LogTemp, Warning, TEXT("Hit location: %s"), *HitLocation.ToString())
		GetControlledTank()->AimAt(HitLocation);
	}

}

// Get world location of linetrace through crosshair, true if hits lanscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	// Find the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

	// "De-project" the screen position of the crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection)) {
		// Line-trace along that look direction and see what we hit (up to max range)
		return GetLookVectorHitLocation(LookDirection, HitLocation);
	}

	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector &LookDirection) const
{
	FVector CameraLocation; // To be discarded
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraLocation, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + LookDirection * LineTraceRange;

	bool LineTraceSuccess = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility
	);

	if (LineTraceSuccess) {
		HitLocation = HitResult.Location;
		return true;
	}

	return false;
}
