#pragma once

#include "CoreMinimal.h"
#include "Enemigo.h"
#include "EnemigoTerrestre.generated.h"

UCLASS(Abstract)
class NAVESUSFX_012026_API AEnemigoTerrestre : public AEnemigo
{
	GENERATED_BODY()

public:
	AEnemigoTerrestre();

protected:
	float AlturaSuelo;

	virtual void ActualizarMovimiento(float DeltaTime) override;
};
