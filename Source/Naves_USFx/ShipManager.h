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

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere)
    int32 NumberOfShips;

    UPROPERTY(EditAnywhere)
    TSubclassOf<AShip> ShipClassToSpawn;

    bool bIsInFormation;
    FTimerHandle StateTimerHandle;

    TArray<AShip*> Fleet;

    void SpawnFleet();
    void ToggleState();
};