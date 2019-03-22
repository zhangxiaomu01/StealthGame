// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSAIGuard.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"


// Sets default values
AFPSAIGuard::AFPSAIGuard()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	sensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("SensingComp"));
	sensingComp->OnSeePawn.AddDynamic(this, &AFPSAIGuard::OnSeenPawn);
	sensingComp->OnHearNoise.AddDynamic(this, &AFPSAIGuard::OnHeardPawn);

}

// Called when the game starts or when spawned
void AFPSAIGuard::BeginPlay()
{
	Super::BeginPlay();

}

void AFPSAIGuard::OnSeenPawn(APawn * seenPawn)
{
	if (!seenPawn) {
		return;
	}
	DrawDebugSphere(GetWorld(), seenPawn->GetActorLocation(), 32.0f, 12, FColor::Red, false, 5.0f);
}

void AFPSAIGuard::OnHeardPawn(APawn * noiseInstigator, const FVector & Location, float Volume)
{
	if (!noiseInstigator)
		return;
	DrawDebugSphere(GetWorld(), Location, 32.0f, 12, FColor::Blue, false, 5.0f);
}

// Called every frame
void AFPSAIGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


