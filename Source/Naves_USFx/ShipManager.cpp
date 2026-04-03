#include "ShipManager.h"
#include "Ship.h"
#include "GeneradorDeCamino.h" // Importante para leer la Lista
#include "Kismet/GameplayStatics.h"

AShipManager::AShipManager()
{
    PrimaryActorTick.bCanEverTick = true;
    NumberOfShips = 20;
    bIsInFormation = false;

    ShipClassToSpawn = AShip::StaticClass();
}

void AShipManager::BeginPlay()
{
    Super::BeginPlay();

    if (ShipClassToSpawn)
    {
        SpawnFleet();
        // Cambia de estado cada 5 segundos
        GetWorld()->GetTimerManager().SetTimer(StateTimerHandle, this, &AShipManager::ToggleState, 5.0f, true);
    }
}

void AShipManager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AShipManager::SpawnFleet()
{
    FVector SpawnOrigin = GetActorLocation();

    for (int32 i = 0; i < NumberOfShips; i++)
    {
        FVector RandomOffset = FVector(FMath::RandRange(-1000.0f, 1000.0f), FMath::RandRange(-1000.0f, 1000.0f), FMath::RandRange(100.0f, 500.0f));
        FVector SpawnPos = SpawnOrigin + RandomOffset;
        FRotator SpawnRot = FRotator(0.0f, FMath::RandRange(0.0f, 360.0f), 0.0f);

        AShip* NewShip = GetWorld()->SpawnActor<AShip>(ShipClassToSpawn, SpawnPos, SpawnRot);
        if (NewShip)
        {
            Fleet.Add(NewShip);
        }
    }
}

void AShipManager::ToggleState()
{
    bIsInFormation = !bIsInFormation;

    if (bIsInFormation)
    {
        // 1. Buscar el GeneradorDeCamino en el escenario
        AActor* ActorGenerador = UGameplayStatics::GetActorOfClass(GetWorld(), AGeneradorDeCamino::StaticClass());
        AGeneradorDeCamino* Generador = Cast<AGeneradorDeCamino>(ActorGenerador);

        if (Generador)
        {
            // 2. Obtener los puntos generados por tu Lista<AActor*>
            TArray<FVector> PuntosDelCamino = Generador->ObtenerPuntosDeCamino();

            if (PuntosDelCamino.Num() > 0)
            {
                // 3. Ordenar a la flota que siga la ruta
                for (int32 i = 0; i < Fleet.Num(); i++)
                {
                    Fleet[i]->CommandFollowPath(PuntosDelCamino);
                }
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("GeneradorDeCamino encontrado, pero la lista esta vacia."));
            }
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("No se encontro ningun GeneradorDeCamino en el mapa."));
        }
    }
    else
    {
        // Vuelven a moverse libremente
        for (AShip* Ship : Fleet)
        {
            Ship->CommandFreeRoam();
        }
    }
}