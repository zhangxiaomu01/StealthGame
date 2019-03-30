// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
//This class only runs in server
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FPSGameMode.generated.h"

UCLASS()
class AFPSGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Viewpoint")
	TSubclassOf<AActor> viewPointClass;

public:
	AFPSGameMode();

	void CompleteMission(APawn* Investigator, bool isMissionSuccess);

};



