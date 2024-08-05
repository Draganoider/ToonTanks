// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"
#include "BossTower.h"


void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
    if(DeadActor == Tank)
    {
        Tank->HandleDestruction();

        if(ToonTanksPlayerController)
        {
            ToonTanksPlayerController->SetPlayerEnabledState(false);
        }
        GameOver(false);
    }
    else if (ATower* DestroyedTower = Cast<ATower>(DeadActor))
    {
        DestroyedTower->HandleDestruction();

        TargetTowers--;

        if(TargetTowers == 0)
        {
            GameOver(true);
        }
    }
}

void AToonTanksGameMode::BeginPlay()
{
    Super::BeginPlay();

    HandleGameStart();

    StartTimer();
}

void AToonTanksGameMode::HandleGameStart()
{
    TargetTowers = GetTargetTowerCount();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

    StartGame();

    if(ToonTanksPlayerController)
    {
        ToonTanksPlayerController->SetPlayerEnabledState(false);

        FTimerHandle PlayerEnableTimerHandle;

        FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(
            ToonTanksPlayerController,
            &AToonTanksPlayerController::SetPlayerEnabledState,
            true);

        GetWorldTimerManager().SetTimer(
        PlayerEnableTimerHandle,
        PlayerEnableTimerDelegate,
        StartDelay,
        false
        );
    }
}

int32 AToonTanksGameMode::GetTargetTowerCount()
{
    TArray<AActor*> Towers;

    TArray<AActor*> BossTowers;

    UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);

    UGameplayStatics::GetAllActorsOfClass(this, ABossTower::StaticClass(), BossTowers);

    int32 TotalCount = Towers.Num() + BossTowers.Num() - 1;
    UE_LOG(LogTemp, Warning, TEXT("Total Targets %d"), TotalCount);

    return Towers.Num() + BossTowers.Num() - 1;
}