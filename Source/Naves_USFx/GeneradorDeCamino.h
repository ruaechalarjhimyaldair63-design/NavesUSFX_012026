#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Lista.h"
#include "GeneradorDeCamino.generated.h"

/**
 * Genera una cadena de bloques del escenario y los guarda en una Lista enlazada.
 * Los puntos del camino sirven para IA (NavMesh / MoveTo) y para lógica del jugador.
 */
UCLASS()
class NAVES_USFX_API AGeneradorDeCamino : public AActor
{
	GENERATED_BODY()

public:
	AGeneradorDeCamino();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	/** Clase del actor-bloque (suelo, pasarela, etc.) asignada en el editor. */
	UPROPERTY(EditAnywhere, Category = "Configuracion Camino")
	TSubclassOf<AActor> ClaseBloque;

	/** Si ClaseBloque no se asigna, se crea un bloque visible con el mesh Cube. */
	UPROPERTY(EditAnywhere, Category = "Configuracion Camino")
	bool bUsarCuboPorDefectoSiNoHayClase;

	/** Número de bloques consecutivos del camino. */
	UPROPERTY(EditAnywhere, Category = "Configuracion Camino", meta = (ClampMin = "1"))
	int32 CantidadDeBloques;

	/** Separación entre el origen de cada bloque (cm). */
	UPROPERTY(EditAnywhere, Category = "Configuracion Camino")
	float EspacioEntreBloques;

	/** Dirección en la que se colocan los bloques (normalmente Y o X del nivel). */
	UPROPERTY(EditAnywhere, Category = "Configuracion Camino")
	FVector DireccionCamino;

	/** Tras generar bloques, recalcula el NavMesh para que enemigos/jugador con IA encuentren camino. */
	UPROPERTY(EditAnywhere, Category = "Configuracion Camino")
	bool bReconstruirNavMeshAlGenerar;

	/** Puntos de recorrido (centro de cada bloque) para MoveTo, splines o lógica propia. */
	UFUNCTION(BlueprintCallable, Category = "Camino")
	TArray<FVector> ObtenerPuntosDeCamino() const;

	UFUNCTION(BlueprintCallable, Category = "Camino")
	int32 ObtenerNumeroDeBloques() const;

	UFUNCTION(BlueprintCallable, Category = "Camino")
	AActor* ObtenerBloqueEn(int32 Indice) const;

private:
	Lista<AActor*> CaminoEscenario;

	void ConstruirCamino();
};
