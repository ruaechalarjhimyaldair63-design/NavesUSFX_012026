#include "ATCamion.h"

ATCamion::ATCamion()
{
	Velocidad = 160.0f;
	AlturaSuelo = 100.0f;
	Direccion = FVector(1.0f, 0.15f, 0.0f).GetSafeNormal();
}
