#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ship.generated.h"

UENUM()
enum class EShipState : uint8
{
    FreeRoaming,
    MovingToFormation,
    InFormation
};

UCLASS()
class NAVES_USFX_API AShip : public AActor
{
    GENERATED_BODY()

public:
    AShip();
    virtual void Tick(float DeltaTime) override;

    // Funciones para que el Manager controle a la nave
    void CommandFreeRoam();
    void CommandFormation(FVector TargetPosition, AActor* ReferencePawn);

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* MeshComp;

private:
    EShipState CurrentState;

    float FreeRoamSpeed;
    float RoamTurnRate;

    FVector StartPos;
    FVector TargetPos;
    AActor* PlayerPawn;
    float TransitionAlpha;
    float TransitionSpeed;
};