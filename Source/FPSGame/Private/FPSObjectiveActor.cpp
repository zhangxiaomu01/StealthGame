// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSObjectiveActor.h"
#include"Components/StaticMeshComponent.h"
#include "components/SphereComponent.h"
#include "kismet/GameplayStatics.h"
#include "FPSCharacter.h"


// Sets default values
AFPSObjectiveActor::AFPSObjectiveActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = meshComp;
	
	sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	sphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	sphereComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	sphereComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	sphereComp->SetupAttachment(meshComp);
	
}

// Called when the game starts or when spawned
void AFPSObjectiveActor::BeginPlay()
{
	Super::BeginPlay();
	//PlayParticleEffects();
}


// Called every frame
void AFPSObjectiveActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFPSObjectiveActor::NotifyActorBeginOverlap(AActor * OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	PlayParticleEffects();

	AFPSCharacter* fpsCharacter = Cast<AFPSCharacter>(OtherActor);
	if (fpsCharacter) {
		fpsCharacter->isPickedup = true;
		this->Destroy();
	}

}

void AFPSObjectiveActor::PlayParticleEffects()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, pickupParticle, GetActorLocation());

}

