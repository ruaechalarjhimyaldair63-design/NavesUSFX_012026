#include "ShipManager.h"
#include "Ship.h"
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
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
    if (!PlayerPawn) return;

    bIsInFormation = !bIsInFormation;

    if (bIsInFormation)
    {
        FVector PawnLoc = PlayerPawn->GetActorLocation();
        FVector PawnForward = PlayerPawn->GetActorForwardVector();
        FVector PawnRight = PlayerPawn->GetActorRightVector();

        FVector FormationCenter = PawnLoc + (PawnForward * 1000.0f);

        int32 Columns = 5;
        float Spacing = 200.0f;

        for (int32 i = 0; i < Fleet.Num(); i++)
        {
            int32 Row = i / Columns;
            int32 Col = i % Columns;

            FVector GridOffset = (PawnRight * (Col - Columns / 2) * Spacing) + (PawnForward * Row * Spacing);
            FVector TargetPos = FormationCenter + GridOffset;

            Fleet[i]->CommandFormation(TargetPos, PlayerPawn);
        }
    }
    else
    {
        for (AShip* Ship : Fleet)
        {
            Ship->CommandFreeRoam();
        }
    }
}