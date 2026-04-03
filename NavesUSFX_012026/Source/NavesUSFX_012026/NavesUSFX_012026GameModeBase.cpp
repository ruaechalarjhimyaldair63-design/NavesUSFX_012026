#include "NavesUSFX_012026GameModeBase.h"
#include "Enemigo.h"
#include "EAHelicoptero.h"
#include "EAAvion.h"
#include "EADron.h"
#include "ATSoldado.h"
#include "ATTanque.h"
#include "ATCamion.h"
#include "ATBlindado.h"
#include "EABarco.h"
#include "EALancha.h"
#include "EAMotoAcuatica.h"
#include "Engine/World.h"
#include "TimerManager.h"

ANavesUSFX_012026GameModeBase::ANavesUSFX_012026GameModeBase()
{
	bCuadrilla2Desplegada = false;
	SegundosDesaparicionCuadrilla1 = 12.0f;
}

void ANavesUSFX_012026GameModeBase::BeginPlay()
{
	Super::BeginPlay();

	SpawnCuadrilla1();

	if (UWorld* const World = GetWorld())
	{
		World->GetTimerManager().SetTimer(
			TemporizadorDesaparicionCuadrilla1,
			this,
			&ANavesUSFX_012026GameModeBase::DestruirRestantesCuadrilla1TrasTemporizador,
			SegundosDesaparicionCuadrilla1,
			false);
	}
}

void ANavesUSFX_012026GameModeBase::NotificarEnemigoDestruido(AEnemigo* Enemigo)
{
	if (!Enemigo)
	{
		return;
	}

	Cuadrilla1.RemoveSingle(Enemigo);
	Cuadrilla2.RemoveSingle(Enemigo);
	IntentarDesplegarCuadrilla2();
}

void ANavesUSFX_012026GameModeBase::IntentarDesplegarCuadrilla2()
{
	if (bCuadrilla2Desplegada)
	{
		return;
	}

	for (AEnemigo* Miembro : Cuadrilla1)
	{
		if (IsValid(Miembro))
		{
			return;
		}
	}

	SpawnCuadrilla2();
	bCuadrilla2Desplegada = true;
}

void ANavesUSFX_012026GameModeBase::DestruirRestantesCuadrilla1TrasTemporizador()
{
	TArray<AEnemigo*> Copia = Cuadrilla1;
	for (AEnemigo* Miembro : Copia)
	{
		if (IsValid(Miembro))
		{
			Miembro->Destroy();
		}
	}
}

void ANavesUSFX_012026GameModeBase::SpawnCuadrilla1()
{
	UWorld* const World = GetWorld();
	if (!World)
	{
		return;
	}

	const TArray<UClass*> Tipos = {
		AEAHelicoptero::StaticClass(),
		AEAAvion::StaticClass(),
		AEADron::StaticClass(),
		AEAHelicoptero::StaticClass(),
		AEADron::StaticClass()
	};

	for (int32 i = 0; i < Tipos.Num(); ++i)
	{
		const FVector Ubicacion(
			FMath::RandRange(-800, 800),
			FMath::RandRange(-800, 800),
			0.0f);

		AEnemigo* const Nuevo = World->SpawnActor<AEnemigo>(Tipos[i], Ubicacion, FRotator::ZeroRotator);
		if (Nuevo)
		{
			Cuadrilla1.Add(Nuevo);
		}
	}
}

void ANavesUSFX_012026GameModeBase::SpawnCuadrilla2()
{
	UWorld* const World = GetWorld();
	if (!World)
	{
		return;
	}

	const TArray<UClass*> Tipos = {
		ATSoldado::StaticClass(),
		ATTanque::StaticClass(),
		ATCamion::StaticClass(),
		ATBlindado::StaticClass(),
		AEABarco::StaticClass(),
		AEALancha::StaticClass(),
		AEAMotoAcuatica::StaticClass()
	};

	for (int32 i = 0; i < Tipos.Num(); ++i)
	{
		const FVector Ubicacion(
			FMath::RandRange(-600, 600),
			FMath::RandRange(-600, 600),
			0.0f);

		AEnemigo* const Nuevo = World->SpawnActor<AEnemigo>(Tipos[i], Ubicacion, FRotator::ZeroRotator);
		if (Nuevo)
		{
			Cuadrilla2.Add(Nuevo);
		}
	}
}
