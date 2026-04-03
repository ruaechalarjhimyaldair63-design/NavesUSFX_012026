#include "Ship.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

AShip::AShip()
{
    PrimaryActorTick.bCanEverTick = true;

    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
    RootComponent = MeshComp;

    // Cargar un cono básico de Unreal para visualizar la nave
    static ConstructorHelpers::FObjectFinder<UStaticMesh> ConeMesh(TEXT("StaticMesh'/Engine/BasicShapes/Cone.Cone'"));
    if (ConeMesh.Succeeded())
    {
        MeshComp->SetStaticMesh(ConeMesh.Object);
        MeshComp->SetRelativeScale3D(FVector(0.5f, 0.5f, 1.0f));
        MeshComp->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));
    }

    CurrentState = EShipState::FreeRoaming;
    FreeRoamSpeed = FMath::RandRange(300.0f, 600.0f);
    RoamTurnRate = FMath::RandRange(-45.0f, 45.0f);
    TransitionSpeed = 1.0f; // Tarda 1 segundo en completar el viaje a la formación
}

void AShip::BeginPlay()
{
    Super::BeginPlay();
}

void AShip::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (CurrentState == EShipState::FreeRoaming)
    {
        // Movimiento libre aleatorio
        AddActorLocalOffset(FVector(FreeRoamSpeed * DeltaTime, 0.0f, 0.0f));
        AddActorLocalRotation(FRotator(0.0f, RoamTurnRate * DeltaTime, 0.0f));
    }
    else if (CurrentState == EShipState::MovingToFormation)
    {
        if (!PlayerPawn) return;

        TransitionAlpha += DeltaTime * TransitionSpeed;

        if (TransitionAlpha >= 1.0f)
        {
            TransitionAlpha = 1.0f;
            CurrentState = EShipState::InFormation;
        }

        FVector BasePos = FMath::Lerp(StartPos, TargetPos, TransitionAlpha);

        // --- Efecto de Pulso Radial Dinámico ---
        FVector PawnLoc = PlayerPawn->GetActorLocation();
        FVector RadialDir = (BasePos - PawnLoc).GetSafeNormal();
        float Distance = FVector::Distance(PawnLoc, BasePos);

        float TimeSecs = GetWorld()->GetTimeSeconds();
        float Amplitude = 200.0f;
        float Frequency = 10.0f;
        float WaveLength = 0.015f;

        float SineWave = FMath::Sin(TimeSecs * Frequency - Distance * WaveLength);
        FVector Offset = RadialDir * SineWave * Amplitude * (1.0f - TransitionAlpha);

        SetActorLocation(BasePos + Offset);

        FRotator TargetRot = (TargetPos - GetActorLocation()).Rotation();
        SetActorRotation(FMath::RInterpTo(GetActorRotation(), TargetRot, DeltaTime, 5.0f));
    }
    else if (CurrentState == EShipState::InFormation)
    {
        SetActorLocation(TargetPos);
    }
    else if (CurrentState == EShipState::FollowingPath && PathPoints.Num() > 0)
    {
        // 1. Obtener la posición del bloque actual
        FVector TargetPoint = PathPoints[CurrentWaypointIndex];

        // 2. Calcular la dirección y moverse
        FVector MoveDir = (TargetPoint - GetActorLocation()).GetSafeNormal();
        AddActorLocalOffset(MoveDir * PathMovementSpeed * DeltaTime);

        // 3. Rotar la nave para que mire hacia donde se mueve
        FRotator TargetRot = MoveDir.Rotation();
        SetActorRotation(FMath::RInterpTo(GetActorRotation(), TargetRot, DeltaTime, 5.0f));

        // 4. Comprobar si ya llegamos al bloque (margen de 50 unidades)
        float DistanceToTarget = FVector::Distance(GetActorLocation(), TargetPoint);
        if (DistanceToTarget < 50.0f)
        {
            CurrentWaypointIndex++; // Pasar al siguiente bloque

            // Si llegamos al final de la lista, volver al inicio (bucle infinito en el camino)
            if (CurrentWaypointIndex >= PathPoints.Num())
            {
                CurrentWaypointIndex = 0;
            }
        }
    }
}

void AShip::CommandFreeRoam()
{
    CurrentState = EShipState::FreeRoaming;
}

void AShip::CommandFormation(FVector TargetPosition, AActor* ReferencePawn)
{
    CurrentState = EShipState::MovingToFormation;
    StartPos = GetActorLocation();
    TargetPos = TargetPosition;
    PlayerPawn = ReferencePawn;
    TransitionAlpha = 0.0f;
}

void AShip::CommandFollowPath(TArray<FVector> PathToFollow)
{
    if (PathToFollow.Num() > 0)
    {
        PathPoints = PathToFollow;
        CurrentWaypointIndex = 0; // Empezar en el primer bloque
        CurrentState = EShipState::FollowingPath;
    }
}