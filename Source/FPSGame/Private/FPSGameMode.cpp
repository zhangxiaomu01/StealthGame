// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.


#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "FPSGameState.h"
#include "FPSPlayerController.h"


AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
	
	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();

	GameStateClass = AFPSGameState::StaticClass();
}

void AFPSGameMode::CompleteMission(APawn * Investigator, bool isMissionSuccess)
{
	if (Investigator) {
		//Investigator->DisableInput(nullptr);

		if (viewPointClass) {
			TArray<AActor*> viewActors;
			UGameplayStatics::GetAllActorsOfClass(this, viewPointClass, viewActors);

			if (viewActors.Num() > 0) {

				AActor* viewActor = viewActors[0];

				for (FConstPlayerControllerIterator it = GetWorld()->GetPlayerControllerIterator(); it; it++) {
					AFPSPlayerController* aPlayerController = Cast<AFPSPlayerController>(it->Get());
					if (aPlayerController) {
						aPlayerController->SetViewTargetWithBlend(viewActor, 0.5f, EViewTargetBlendFunction::VTBlend_Cubic);
					}
				}

			}
		}
		else{
			UE_LOG(LogTemp, Warning, TEXT("No view point class specified!"));
		}
		
	}

	//Handles disable input for all clients
	AFPSGameState* GS = GetGameState<AFPSGameState>();
	if (GS) {
		GS->MulticastOnMissionCompleted(Investigator, isMissionSuccess);
	}

}
