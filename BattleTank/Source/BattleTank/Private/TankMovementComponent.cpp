// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

// Sets default values
void UTankMovementComponent::Initialise(UTankTrack * LeftTrack, UTankTrack * RightTrack)
{
	if (!LeftTrack || !RightTrack) { return; }
	this->LeftTrack = LeftTrack;
	this->RightTrack = RightTrack;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);

	// TODO prevent double speed from inputs (triggers)
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);

	// TODO prevent double speed from inputs (triggers)
}
