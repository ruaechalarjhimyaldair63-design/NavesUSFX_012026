#pragma once

#include "CoreMinimal.h"
#include "Enemigo.h"
#include "EnemigoAereo.generated.h"

UCLASS(Abstract)
class NAVESUSFX_012026_API AEnemigoAereo : public AEnemigo
{
	GENERATED_BODY()

public:
	AEnemigoAereo();

protected:
	float AltitudVuelo;

	virtual void ActualizarMovimiento(float DeltaTime) override;
};
