// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSObjectiveActor.generated.h"

class USphereComponent;
class UParticleSystem;

UCLASS()
class FPSGAME_API AFPSObjectiveActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSObjectiveActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnyWhere, Category = "Components")
		UStaticMeshComponent* meshComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		USphereComponent* sphereComp;

	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
		UParticleSystem* pickupParticle;
	
	void PlayParticleEffects();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	
};
