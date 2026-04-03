#include "EALancha.h"

AEALancha::AEALancha()
{
	Velocidad = 240.0f;
	NivelSuperficieAgua = 52.0f;
	Direccion = FVector(0.6f, 0.8f, 0.0f).GetSafeNormal();
}
