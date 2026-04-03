#include "ATBlindado.h"

ATBlindado::ATBlindado()
{
	Velocidad = 140.0f;
	AlturaSuelo = 102.0f;
	Direccion = FVector(0.9f, 0.4f, 0.0f).GetSafeNormal();
}
