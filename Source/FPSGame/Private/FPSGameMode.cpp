// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
	
	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();
}

void AFPSGameMode::CompleteMission(APawn * Investigator, bool isMissionSuccess)
{
	if (Investigator) {
		Investigator->DisableInput(nullptr);

		if (viewPointClass) {
			TArray<AActor*> viewActors;
			UGameplayStatics::GetAllActorsOfClass(this, viewPointClass, viewActors);

			if (viewActors.Num() > 0) {

				AActor* viewActor = viewActors[0];
				APlayerController* aPlayerController = Cast<APlayerController>(Investigator->GetController());
				if (aPlayerController) {
					aPlayerController->SetViewTargetWithBlend(viewActor, 0.5f, EViewTargetBlendFunction::VTBlend_Cubic);
				}
			}
		}
		else{
			UE_LOG(LogTemp, Warning, TEXT("No view point class specified!"));
		}
		
	}

	OnMissionCompleted(Investigator, isMissionSuccess);
}
