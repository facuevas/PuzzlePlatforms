// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	AMovingPlatform();

	void AddActiveTrigger();

	void RemoveActiveTrigger();

protected:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category = "Properties")
	float Speed;

	UPROPERTY(EditAnywhere, Category = "Properties", Meta = (MakeEditWidget = true))
	FVector TargetLocation;

	void PlatformCycle(float DeltaSeconds);


private:

	FVector GlobalTargetLocation;

	FVector GlobalStartLocation;

	UPROPERTY(EditAnywhere)
	int ActiveTriggers;
};
