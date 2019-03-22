// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSAIGuard.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"
#include "FPSGameMode.h"



// Sets default values
AFPSAIGuard::AFPSAIGuard()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	sensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("SensingComp"));
	sensingComp->OnSeePawn.AddDynamic(this, &AFPSAIGuard::OnSeenPawn);
	sensingComp->OnHearNoise.AddDynamic(this, &AFPSAIGuard::OnHeardPawn);
	
	AIState = EAIState::Idle;
}

// Called when the game starts or when spawned
void AFPSAIGuard::BeginPlay()
{
	Super::BeginPlay();
	originalRot = GetActorRotation();
}

void AFPSAIGuard::OnSeenPawn(APawn * seenPawn)
{
	if (!seenPawn) {
		return;
	}
	DrawDebugSphere(GetWorld(), seenPawn->GetActorLocation(), 32.0f, 12, FColor::Red, false, 5.0f);
	AFPSGameMode* myGameMode = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());
	if (myGameMode) {
		myGameMode->CompleteMission(seenPawn, false);
	}
	SetAIState(EAIState::Alerted);
}

void AFPSAIGuard::OnHeardPawn(APawn * noiseInstigator, const FVector & Location, float Volume)
{
	if (AIState == EAIState::Alerted)
		return;

	if (!noiseInstigator)
		return;
	DrawDebugSphere(GetWorld(), Location, 32.0f, 12, FColor::Blue, false, 5.0f);

	//Guard Dsitraction Behavior
	FVector soundDir = Location - GetActorLocation();
	soundDir.Normalize();

	FRotator AIRotator = FRotationMatrix::MakeFromX(soundDir).Rotator();
	AIRotator.Pitch = 0.0f;
	AIRotator.Roll = 0.0f;

	SetActorRotation(AIRotator);
	//Set timer
	GetWorldTimerManager().ClearTimer(guardDistractionTimerHandle);
	GetWorldTimerManager().SetTimer(guardDistractionTimerHandle, this, &AFPSAIGuard::ResetOrientation, 3.0f);

	SetAIState(EAIState::Suspicious);
}

void AFPSAIGuard::ResetOrientation()
{
	if (AIState == EAIState::Alerted)
		return;
	SetActorRotation(originalRot);
	SetAIState( EAIState::Idle);
}

void AFPSAIGuard::SetAIState(EAIState newState)
{
	if (AIState == newState)
		return;

	AIState = newState;

	StateChanged(newState);
}



// Called every frame
void AFPSAIGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


