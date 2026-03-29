#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShipManager.generated.h"

class AShip;

UCLASS()
class NAVES_USFX_API AShipManager : public AActor
{
    GENERATED_BODY()

public:
    AShipManager();
    virtual void Tick(float DeltaTime) override;

protected:
    virtual void BeginPlay() override;

private:
    UClass* ShipClassToSpawn;
    int32 NumberOfShips;
    TArray<AShip*> Fleet;
    FTimerHandle StateTimerHandle;
    bool bIsInFormation;

    void SpawnFleet();
    void ToggleState();
};