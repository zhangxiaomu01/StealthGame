#pragma once
#include "Engine/GameEngine.h"
//This defines the debug message to output to viewport
#define DebugMessage(x,...) if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString::Printf(TEXT(x), __VA_ARGS__));}
