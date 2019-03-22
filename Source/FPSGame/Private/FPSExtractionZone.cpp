// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSExtractionZone.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "FPSCharacter.h"
#include "FPSGameMode.h"
#include "Kismet/GameplayStatics.h"


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

	decalComp = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComp"));
	decalComp->DecalSize = FVector(200.0f);
	decalComp->SetWorldRotation(FQuat(0.0f, 90.0f, 0.0f, 1.0f));
	decalComp->SetupAttachment(RootComponent);
}

void AFPSExtractionZone::HandleOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	//Make sure that parameter has exactly the same name....
	UE_LOG(LogTemp, Log, TEXT("Player in Extraction Zone!"));
	AFPSCharacter* myCharacter = Cast<AFPSCharacter>(OtherActor);

	if (myCharacter == nullptr) {
		return;
	}

	if (myCharacter->isPickedup) {
		AFPSGameMode* myGameMode = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());
		if (myGameMode) {
			myGameMode->CompleteMission(myCharacter, true);
		}
	}
	else {
		UGameplayStatics::PlaySound2D(this, missingSound);
	}
}
