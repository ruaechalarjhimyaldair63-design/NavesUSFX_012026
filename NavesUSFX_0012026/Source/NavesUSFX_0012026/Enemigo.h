#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemigo.generated.h"

UCLASS()
class NAVESUSFX_0012026_API AEnemigo : public AActor
{
	GENERATED_BODY()

public:
	AEnemigo();

protected:
	virtual void BeginPlay() override;

	// Componente de malla para que el enemigo sea visible
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MallaEnemigo;

public:
	virtual void Tick(float DeltaTime) override;

	// Variables de movimiento
	float Velocidad;
	FVector Direccion;
};