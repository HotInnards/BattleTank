// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

// Called when the game starts or when spawned
void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (ControlledTank) { return; }
	else {
		UE_LOG(LogTemp, Error, TEXT("PlayerController not possessing tank."));
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
	return;

}

