#include "NavesUSFX_0012026GameMode.h"
#include "Enemigo.h" 

void ANavesUSFX_0012026GameMode::BeginPlay()
{
	Super::BeginPlay();

	UWorld* const World = GetWorld();

	if (World)
	{
		for (int i = 0; i < 5; i++)
		{
			FVector UbicacionSpawn(FMath::RandRange(-800, 800), FMath::RandRange(-800, 800), 150.0f);
			FRotator RotacionSpawn(0.0f, 0.0f, 0.0f);

			World->SpawnActor<AEnemigo>(AEnemigo::StaticClass(), UbicacionSpawn, RotacionSpawn);
		}
	}
}