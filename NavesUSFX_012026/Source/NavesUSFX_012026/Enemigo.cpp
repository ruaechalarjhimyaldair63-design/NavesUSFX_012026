#include "Enemigo.h"
#include "NavesUSFX_012026GameModeBase.h"
#include "UObject/ConstructorHelpers.h"

AEnemigo::AEnemigo()
{
	PrimaryActorTick.bCanEverTick = true;

	MallaEnemigo = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MallaEnemigo"));
	RootComponent = MallaEnemigo;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MallaCubo(TEXT("/Engine/BasicShapes/Cube.Cube"));
	if (MallaCubo.Succeeded())
	{
		MallaEnemigo->SetStaticMesh(MallaCubo.Object);
	}

	Velocidad = 250.0f;
	Direccion = FVector(1.0f, 0.0f, 0.0f);
}

void AEnemigo::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemigo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ActualizarMovimiento(DeltaTime);
}

void AEnemigo::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (UWorld* const World = GetWorld())
	{
		if (AGameModeBase* AuthGM = World->GetAuthGameMode())
		{
			if (ANavesUSFX_012026GameModeBase* ModoJuego = Cast<ANavesUSFX_012026GameModeBase>(AuthGM))
			{
				ModoJuego->NotificarEnemigoDestruido(this);
			}
		}
	}
	Super::EndPlay(EndPlayReason);
}

void AEnemigo::ActualizarMovimiento(float DeltaTime)
{
}
