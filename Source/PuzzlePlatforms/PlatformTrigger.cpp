// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformTrigger.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "MovingPlatform.h"

// Sets default values
APlatformTrigger::APlatformTrigger()
{
	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	TriggerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));

	if (!ensure(TriggerVolume != nullptr)) return;
	RootComponent = TriggerVolume;

	if (!ensure(TriggerMesh != nullptr)) return;
	TriggerMesh->SetupAttachment(RootComponent);

	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &APlatformTrigger::OnOverlapBegin);
	TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &APlatformTrigger::OnOverlapEnd);
}

void APlatformTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                      UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                      const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		for (AMovingPlatform* Platform : MovingPlatforms)
		{
			Platform->AddActiveTrigger();
		}
	}
}

void APlatformTrigger::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		for (AMovingPlatform* Platform : MovingPlatforms)
		{
			Platform->RemoveActiveTrigger();
		}
	}
}

// Called when the game starts or when spawned
void APlatformTrigger::BeginPlay()
{
	Super::BeginPlay();
}
