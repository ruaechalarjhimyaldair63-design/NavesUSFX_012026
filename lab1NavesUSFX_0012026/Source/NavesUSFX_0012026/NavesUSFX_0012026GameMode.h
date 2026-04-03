#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NavesUSFX_0012026GameMode.generated.h" // <--- LA SOLUCIÓN ESTÁ AQUÍ

UCLASS()
class NAVESUSFX_0012026_API ANavesUSFX_0012026GameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

};