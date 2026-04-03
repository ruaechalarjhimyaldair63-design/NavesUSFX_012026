#include "Enemigo.h"
#include "UObject/ConstructorHelpers.h" // Necesitamos esto para cargar la malla

AEnemigo::AEnemigo()
{
	PrimaryActorTick.bCanEverTick = true;

	// Crear la malla y establecerla como raíz
	MallaEnemigo = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MallaEnemigo"));
	RootComponent = MallaEnemigo;

	// Cargar un cubo básico que ya viene con Unreal Engine
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MallaCubo(TEXT("/Engine/BasicShapes/Cube.Cube"));

	if (MallaCubo.Succeeded())
	{
		MallaEnemigo->SetStaticMesh(MallaCubo.Object);
	}

	// Configuración inicial de movimiento
	Velocidad = 250.0f;
	Direccion = FVector(1.0f, 0.0f, 0.0f); // Se mueve en el eje X
}

void AEnemigo::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemigo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Lógica de movimiento constante
	FVector NuevaUbicacion = GetActorLocation() + (Direccion * Velocidad * DeltaTime);
	SetActorLocation(NuevaUbicacion);

	// Rebote simple si se aleja mucho del centro
	if (FMath::Abs(NuevaUbicacion.X) > 1500.0f)
	{
		Direccion.X *= -1;
	}
}