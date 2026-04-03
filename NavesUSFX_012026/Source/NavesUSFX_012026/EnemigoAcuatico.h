#pragma once

#include "CoreMinimal.h"
#include "Enemigo.h"
#include "EnemigoAcuatico.generated.h"

UCLASS(Abstract)
class NAVESUSFX_012026_API AEnemigoAcuatico : public AEnemigo
{
	GENERATED_BODY()

public:
	AEnemigoAcuatico();

protected:
	float NivelSuperficieAgua;

	virtual void ActualizarMovimiento(float DeltaTime) override;
};
