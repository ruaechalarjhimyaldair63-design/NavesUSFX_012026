#include "EnemigoTerrestre.h"

AEnemigoTerrestre::AEnemigoTerrestre()
{
	AlturaSuelo = 100.0f;
}

void AEnemigoTerrestre::ActualizarMovimiento(float DeltaTime)
{
	const FVector Loc = GetActorLocation();
	FVector Nueva = Loc + Direccion * Velocidad * DeltaTime;
	Nueva.Z = AlturaSuelo;
	SetActorLocation(Nueva);

	if (FMath::Abs(Nueva.X) > 1500.0f)
	{
		Direccion.X *= -1.0f;
	}
}
