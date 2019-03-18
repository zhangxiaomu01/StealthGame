// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSExtractionZone.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"


// Sets default values
AFPSExtractionZone::AFPSExtractionZone()
{
	overlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));
	overlapComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	overlapComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	overlapComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	overlapComp->SetBoxExtent(FVector(200.0f));
	overlapComp->SetHiddenInGame(false);
	RootComponent = overlapComp;

	overlapComp->OnComponentBeginOverlap.AddDynamic(this, &AFPSExtractionZone::HandleOverlap);
}

void AFPSExtractionZone::HandleOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	//Make sure that parameter has exactly the same name....
	UE_LOG(LogTemp, Log, TEXT("Player in Extraction Zone!"));
}
