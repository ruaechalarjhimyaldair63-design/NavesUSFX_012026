#include "EAHelicoptero.h"

AEAHelicoptero::AEAHelicoptero()
{
	Velocidad = 280.0f;
	AltitudVuelo = 520.0f;
	Direccion = FVector(1.0f, 0.25f, 0.0f).GetSafeNormal();
}
