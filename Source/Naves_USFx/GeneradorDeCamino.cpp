#include "GeneradorDeCamino.h"
#include "Engine/World.h"
#include "NavigationSystem.h"
#include "Engine/StaticMesh.h"
#include "Engine/StaticMeshActor.h"
#include "UObject/ConstructorHelpers.h"

AGeneradorDeCamino::AGeneradorDeCamino()
{
	PrimaryActorTick.bCanEverTick = true;
	CantidadDeBloques = 5;
	EspacioEntreBloques = 200.0f;
	DireccionCamino = FVector(0.0f, 1.0f, 0.0f);
	bReconstruirNavMeshAlGenerar = true;
	bUsarCuboPorDefectoSiNoHayClase = true;
}

void AGeneradorDeCamino::BeginPlay()
{
	Super::BeginPlay();
	ConstruirCamino();
}

void AGeneradorDeCamino::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

TArray<FVector> AGeneradorDeCamino::ObtenerPuntosDeCamino() const
{
	TArray<FVector> Puntos;
	const int32 N = CaminoEscenario.ObtenerTamano();
	Puntos.Reserve(N);
	for (int32 i = 0; i < N; i++)
	{
		AActor* Bloque = CaminoEscenario.Obtener(i);
		if (IsValid(Bloque))
		{
			Puntos.Add(Bloque->GetActorLocation());
		}
	}
	return Puntos;
}

int32 AGeneradorDeCamino::ObtenerNumeroDeBloques() const
{
	return CaminoEscenario.ObtenerTamano();
}

AActor* AGeneradorDeCamino::ObtenerBloqueEn(int32 Indice) const
{
	return CaminoEscenario.Obtener(Indice);
}

void AGeneradorDeCamino::ConstruirCamino()
{
	// PEGA ESTA LÍNEA EN SU LUGAR
	UStaticMesh* CubeMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Engine/BasicShapes/Cube.Cube"));

	FVector Dir = DireccionCamino.GetSafeNormal();
	if (Dir.IsNearlyZero())
	{
		Dir = FVector::ForwardVector;
	}

	FVector PosicionActual = GetActorLocation();
	const FRotator RotacionActual = GetActorRotation();

	for (int32 i = 0; i < CantidadDeBloques; i++)
	{
		AActor* NuevoBloque = nullptr;

		if (ClaseBloque)
		{
			NuevoBloque = GetWorld()->SpawnActor<AActor>(ClaseBloque, PosicionActual, RotacionActual);
		}
		else if (bUsarCuboPorDefectoSiNoHayClase)
		{
			AStaticMeshActor* CuboActor = GetWorld()->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass(), PosicionActual, RotacionActual);
			if (CuboActor && CuboActor->GetStaticMeshComponent())
			{
				if (CubeMesh)
				{
					CuboActor->GetStaticMeshComponent()->SetStaticMesh(CubeMesh);
				}
				CuboActor->SetMobility(EComponentMobility::Static);
			}
			NuevoBloque = CuboActor;
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("GeneradorDeCamino: no hay ClaseBloque y el cubo por defecto está desactivado."));
			break;
		}

		if (NuevoBloque != nullptr)
		{
			CaminoEscenario.InsertarFinal(NuevoBloque);
			PosicionActual += Dir * EspacioEntreBloques;
		}
	}

	UE_LOG(LogTemp, Log, TEXT("GeneradorDeCamino: %d bloques en la lista enlazada."), CaminoEscenario.ObtenerTamano());

	if (bReconstruirNavMeshAlGenerar)
	{
		if (UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld()))
		{
			NavSys->Build();
		}
	}
}
