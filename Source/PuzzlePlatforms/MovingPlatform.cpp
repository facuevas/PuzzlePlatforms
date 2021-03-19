// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

#include "Engine/EngineTypes.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;
	SetMobility(EComponentMobility::Movable);

	// Speed of moving platform.
	Speed = 20.f;
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		SetReplicates(true); // sets the actor replication
		SetReplicateMovement(true); // sets the actor movement replication
	}
}

void AMovingPlatform::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// HasAuthority checks if player is a server or a client
	// If a player HasAuthority, they are the server
	// and the box moves
	// else they are a client
	// and see no changes with the box.
	if (HasAuthority())
	{
		FVector Location = GetActorLocation();
		Location += FVector(Speed * DeltaSeconds, 0.f, 0.f);
		SetActorLocation(Location);
	}
	
}
