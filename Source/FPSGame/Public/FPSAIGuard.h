// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSAIGuard.generated.h"


class UPawnSensingComponent;

//UENUM can only work with uint8 type
//Make sure to expose this first
UENUM(BlueprintType)
enum class EAIState : uint8 {
	Idle,
	Suspicious,
	Alerted
};

UCLASS()
class FPSGAME_API AFPSAIGuard : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSAIGuard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "SensingComp")
	UPawnSensingComponent* sensingComp;

	UPROPERTY(EditInstanceOnly, Category = "AI")
	bool isPatrol;

	UPROPERTY(EditInstanceOnly, Category = "AI", meta = (EditCondition = isPatrol))
	TArray<AActor*> patrolPoints;

	UFUNCTION()
	void OnSeenPawn(APawn* seenPawn);

	UFUNCTION()
	void OnHeardPawn(APawn* noiseInstigator, const FVector& Location, float Volume);

	UFUNCTION()
	void ResetOrientation();

	UFUNCTION(BlueprintImplementableEvent, Category = "AI")
	void StateChanged(EAIState newState);

	UPROPERTY(ReplicatedUsing = OnRep_GuardState)
	EAIState AIState;

	UFUNCTION()
	void OnRep_GuardState();

	FRotator originalRot;

	FTimerHandle guardDistractionTimerHandle;

	AActor* currentPatrolPoint;

	void MoveToNextPatrolPoint();

	void SetAIState(EAIState newState);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
