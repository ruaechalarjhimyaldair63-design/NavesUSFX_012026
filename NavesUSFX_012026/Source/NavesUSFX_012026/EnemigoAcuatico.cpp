#include "EnemigoAcuatico.h"

AEnemigoAcuatico::AEnemigoAcuatico()
{
	NivelSuperficieAgua = 50.0f;
}

void AEnemigoAcuatico::ActualizarMovimiento(float DeltaTime)
{
	const FVector Loc = GetActorLocation();
	FVector Nueva = Loc + Direccion * Velocidad * DeltaTime;
	Nueva.Z = NivelSuperficieAgua;
	SetActorLocation(Nueva);

	if (FMath::Abs(Nueva.X) > 1500.0f)
	{
		Direccion.X *= -1.0f;
	}
	if (FMath::Abs(Nueva.Y) > 1500.0f)
	{
		Direccion.Y *= -1.0f;
	}
}
