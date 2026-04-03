#include "ATTanque.h"

ATTanque::ATTanque()
{
	Velocidad = 120.0f;
	AlturaSuelo = 105.0f;
	Direccion = FVector(0.7f, 0.7f, 0.0f).GetSafeNormal();
}
