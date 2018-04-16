// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	ATank * GetControlledTank() const;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// Start the tank moving the barrel so that a shot would hit where the crosshair intersects the world
	void AimTowardsCrossHair();

	// Return an OUT parameter, true if hit landscape
	bool GetSightRayHitLocation(FVector& HitLocation) const;
	
};
