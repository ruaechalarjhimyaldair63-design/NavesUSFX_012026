#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SwarmGameMode.generated.h"

UCLASS()
class NAVES_USFX_API ASwarmGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void StartPlay() override;
};