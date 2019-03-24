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

	UPROPERTY(EditorInstanceOnly, Category = "AI")
	bool isPatrol;


	UFUNCTION()
	void OnSeenPawn(APawn* seenPawn);

	UFUNCTION()
	void OnHeardPawn(APawn* noiseInstigator, const FVector& Location, float Volume);

	UFUNCTION()
	void ResetOrientation();

	UFUNCTION(BlueprintImplementableEvent, Category = "AI")
	void StateChanged(EAIState newState);

	FRotator originalRot;

	FTimerHandle guardDistractionTimerHandle;

	EAIState AIState;
	void SetAIState(EAIState newState);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
