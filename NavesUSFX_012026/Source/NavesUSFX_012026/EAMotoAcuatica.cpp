#include "EAMotoAcuatica.h"

AEAMotoAcuatica::AEAMotoAcuatica()
{
	Velocidad = 300.0f;
	NivelSuperficieAgua = 48.0f;
	Direccion = FVector(1.0f, -0.3f, 0.0f).GetSafeNormal();
}
