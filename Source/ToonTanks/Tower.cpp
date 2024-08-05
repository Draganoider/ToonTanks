// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    
    if (InFireRange())
    {
        RotateTurret(Tank->GetActorLocation());
    }
    

    
}

void ATower::HandleDestruction()
{
    Super::HandleDestruction();

    Destroy();
}

void ATower::BeginPlay()
{
    Super::BeginPlay();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

    ResetFireRate(); // Initialize fire rate and set the timer
}

void ATower::CheckFireCondition()
{
    if (Tank == nullptr)
    {
        return;
    }


    if (InFireRange() && Tank->bAlive)
    {
        Fire();
    }

    ResetFireRate();
}

bool ATower::InFireRange()
{
    if (Tank)
    {
        float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
        if (Distance <= FireRange)
        {
            return true;
        }

    }
    return false;
}

void ATower::ResetFireRate()
{
    FireRate = FMath::FRandRange(1.0f, 3.0f); // Generate a random fire rate between 1 and 3 seconds

    GetWorldTimerManager().SetTimer(
        FireRateTimerHandle,
        this,
        &ATower::CheckFireCondition,
        FireRate,
        false); // Set the timer to call CheckFireCondition after the random fire rate
}