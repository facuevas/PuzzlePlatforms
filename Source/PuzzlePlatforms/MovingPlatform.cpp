// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"
#include "Engine/EngineTypes.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;
	SetMobility(EComponentMobility::Movable);

	// Speed of moving platform.
	Speed = 20.f;

	ActiveTriggers = 1;
}

void AMovingPlatform::AddActiveTrigger()
{
	ActiveTriggers++;
}

void AMovingPlatform::RemoveActiveTrigger()
{
	if (ActiveTriggers > 0)
	{
		ActiveTriggers--;
	}
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		SetReplicates(true); // sets the actor replication
		SetReplicateMovement(true); // sets the actor movement replication
	}

	GlobalStartLocation = GetActorLocation();
	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
	// change TargetLocation from relative to global coordinates
}

void AMovingPlatform::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// HasAuthority checks if player is a server or a client
	// If a player HasAuthority, they are the server
	// and the box moves
	// else they are a client
	// and see no changes with the box.
	if (ActiveTriggers > 0)
	{
		if (HasAuthority())
		{
			PlatformCycle(DeltaSeconds);
		}
	}
}

/*
 * Moves the platform back to the target location
 * back to where it was originally placed.
 * Must be used in Tick() due to Delta Time usage
 */
void AMovingPlatform::PlatformCycle(float DeltaSeconds)
{
	FVector Location = GetActorLocation(); // Get the current location of the platform
	const float Distance = FVector::Dist(GlobalTargetLocation, GlobalStartLocation);
	// Get the total distance from start to target
	const float CurrentDistance = FVector::Dist(Location, GlobalStartLocation);
	// Get the current distance from the current location to target

	// If the CurrentDistance is greater than the Distance,
	// Our platform is there.
	// Swap the values to cycle back
	if (CurrentDistance >= Distance)
	{
		FVector Temp = GlobalStartLocation;
		GlobalStartLocation = GlobalTargetLocation;
		GlobalTargetLocation = Temp;
	}

	// Calculate Direction Vector and move the Platform
	FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
	Location += Speed * DeltaSeconds * Direction;
	SetActorLocation(Location);
}
