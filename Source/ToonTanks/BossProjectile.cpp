#include "BossProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"

ABossProjectile::ABossProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovement->bIsHomingProjectile = bIsHomingProjectile;
	ProjectileMovement->HomingAccelerationMagnitude = HomingAccelerationMagnitude;
}

void ABossProjectile::BeginPlay()
{
	Super::BeginPlay();

	if (LaunchSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation(), GetActorRotation());
	}

	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	// Найти цель наведения
	FindHomingTarget();

    GetWorld()->GetTimerManager().SetTimer(HomingTimerHandle, this, &ABossProjectile::StopHoming, HomingDuration, false);
}

void ABossProjectile::SetHomingTarget(AActor* Target)
{
    HomingTarget = Target;

    if (Target)
	{
		ProjectileMovement->HomingTargetComponent = Target->GetRootComponent();
	}
}

void ABossProjectile::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Обновляем ориентацию снаряда, чтобы он смотрел на цель
    if (HomingTarget)
    {
        FVector Direction = (HomingTarget->GetActorLocation() - GetActorLocation()).GetSafeNormal();
        FRotator NewRotation = Direction.Rotation();
        SetActorRotation(NewRotation);
    }
}

void ABossProjectile::FindHomingTarget()
{
	TArray<AActor*> PlayerPawns;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATank::StaticClass(), PlayerPawns);

	if (PlayerPawns.Num() > 0)
	{
		AActor* NearestTarget = nullptr;
		float MinDistance = TNumericLimits<float>::Max();

		for (AActor* PlayerPawn : PlayerPawns)
		{
			float Distance = FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());
			if (Distance < MinDistance)
			{
				MinDistance = Distance;
				NearestTarget = PlayerPawn;
			}
		}

		SetHomingTarget(NearestTarget);
	}
}

void ABossProjectile::StopHoming()
{
    // Отключаем наведение
    ProjectileMovement->bIsHomingProjectile = false;
    HomingTarget = nullptr;
}
