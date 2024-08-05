// Fill out your copyright notice in the Description page of Project Settings.
#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

ATank::ATank()
{
    //PrimaryActorTick.bCanEverTick = true;

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject <UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);

    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);

    PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);

}

void ATank::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    

    if (TankPlayerController)
    {
        FHitResult HitResult;

        TankPlayerController->GetHitResultUnderCursor(
        ECollisionChannel::ECC_Visibility,
        false,
        HitResult);

        /*
        DrawDebugSphere(
        GetWorld(),
        HitResult.ImpactPoint,
        20.f,
        12,
        FColor::Red,
        false,
        -1.f);
        */

        RotateTurret(HitResult.ImpactPoint);
    }
}


void ATank::HandleDestruction()
{
    Super::HandleDestruction();

    SetActorHiddenInGame(true);

    SetActorTickEnabled(false);

    bAlive = false;
}


void ATank::BeginPlay()
{
    Super::BeginPlay();

    TankPlayerController = Cast<APlayerController>(GetController());

    TankPlayerController->bShowMouseCursor = true;

    /*DrawDebugSphere(GetWorld(),
    GetActorLocation()+ FVector(0.f, 0.f, 200.f), 
    100.f,
    12,
    FColor::Red,
    true,
    5.f);
    */
}


void ATank::Move(float Value)
{
    FVector DeltaLocation = FVector::Zero();
    
    DeltaLocation.X = Value * Speed * UGameplayStatics::GetWorldDeltaSeconds(this);

    AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Turn(float Value)
{
    FRotator DeltaRotation = FRotator::ZeroRotator;

    DeltaRotation.Yaw = Value * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this);

    AddActorLocalRotation(DeltaRotation, true);
}

