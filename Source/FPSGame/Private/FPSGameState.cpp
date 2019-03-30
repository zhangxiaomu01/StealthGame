// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSGameState.h"
#include "Engine/World.h"
#include "FPSPlayerController.h"
//#include "DebugMessage.h"

void AFPSGameState::MulticastOnMissionCompleted_Implementation(APawn * Investigator, bool isMissionSuccess)
{

	for (FConstPlayerControllerIterator it = GetWorld()->GetPlayerControllerIterator(); it; it++) {
		AFPSPlayerController* pc = Cast<AFPSPlayerController>(it->Get());
		if (pc && pc->IsLocalController()) {


			pc->OnMissionCompleted(Investigator, isMissionSuccess);
			//DebugMessage("Called");
			APawn* tPawn = pc->GetPawn();
			//We do not check tPawn-> IsLocallyControlled(), since pc already does the check
			if (tPawn) {
				tPawn->DisableInput(pc);
			}

		}
	}
}
