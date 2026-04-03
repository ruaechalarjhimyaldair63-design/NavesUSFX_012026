#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ship.generated.h"

UENUM()
enum class EShipState : uint8
{
    FreeRoaming,
    MovingToFormation,
    InFormation,
    FollowingPath // NUEVO ESTADO
};

UCLASS()
class NAVES_USFX_API AShip : public AActor
{
    GENERATED_BODY()

public:
    AShip();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* MeshComp;

    EShipState CurrentState;

    float FreeRoamSpeed;
    float RoamTurnRate;
    float TransitionSpeed;
    float TransitionAlpha;

    FVector StartPos;
    FVector TargetPos;
    AActor* PlayerPawn;

    void CommandFreeRoam();
    void CommandFormation(FVector TargetPosition, AActor* ReferencePawn);

    // Nueva función para seguir el camino
    void CommandFollowPath(TArray<FVector> PathToFollow);

private:
    // Variables para la lógica de la lista/camino
    TArray<FVector> PathPoints;
    int32 CurrentWaypointIndex;
    float PathMovementSpeed = 500.0f;
};