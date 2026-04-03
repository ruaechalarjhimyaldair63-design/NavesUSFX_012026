#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TimerManager.h"
#include "NavesUSFX_012026GameModeBase.generated.h"

class AEnemigo;

UCLASS()
class NAVESUSFX_012026_API ANavesUSFX_012026GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ANavesUSFX_012026GameModeBase();

	void NotificarEnemigoDestruido(AEnemigo* Enemigo);

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	TArray<AEnemigo*> Cuadrilla1;

	UPROPERTY()
	TArray<AEnemigo*> Cuadrilla2;

	FTimerHandle TemporizadorDesaparicionCuadrilla1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cuadrillas", meta = (ClampMin = "0.5"))
	float SegundosDesaparicionCuadrilla1;

private:
	bool bCuadrilla2Desplegada;

	void SpawnCuadrilla1();
	void SpawnCuadrilla2();
	void DestruirRestantesCuadrilla1TrasTemporizador();
	void IntentarDesplegarCuadrilla2();
};
