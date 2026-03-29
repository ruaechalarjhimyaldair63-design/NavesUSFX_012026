#include "SwarmGameMode.h"
#include "ShipManager.h"

void ASwarmGameMode::StartPlay()
{
    Super::StartPlay();

    if (GetWorld())
    {
        GetWorld()->SpawnActor<AShipManager>(AShipManager::StaticClass(), FVector(0.0f, 0.0f, 0.0f), FRotator::ZeroRotator);
    }
}