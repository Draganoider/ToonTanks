#include "BossTower.h"
#include "BossProjectile.h"
#include "Kismet/GameplayStatics.h"

ABossTower::ABossTower()
{
	// Установи класс проекта для босса
	BossProjectileClass = ABossProjectile::StaticClass();
}

void ABossTower::BeginPlay()
{
	Super::BeginPlay();

	// Заменяем ProjectileClass на BossProjectileClass
	if (BossProjectileClass)
	{
		ProjectileClass = BossProjectileClass;
	}
}

void ABossTower::Fire()
{
	FVector Location = ProjectileSpawnPoint->GetComponentLocation();
	FRotator Rotation = ProjectileSpawnPoint->GetComponentRotation();

	ABossProjectile* Projectile = GetWorld()->SpawnActor<ABossProjectile>(BossProjectileClass, Location, Rotation);
	if (Projectile)
	{
		Projectile->SetOwner(this);
	}
}
