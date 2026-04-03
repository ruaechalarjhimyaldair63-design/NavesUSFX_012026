#include "EADron.h"

AEADron::AEADron()
{
	Velocidad = 220.0f;
	AltitudVuelo = 380.0f;
	Direccion = FVector(0.8f, 0.6f, 0.0f).GetSafeNormal();
}
