#pragma once

#include "CoreMinimal.h"
#include "Tower.h"
#include "BossTower.generated.h"

// Forward declaration
class ABossProjectile;

/**
 *
 */
UCLASS()
class TOONTANKS_API ABossTower : public ATower
{
	GENERATED_BODY()

public:
	ABossTower();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Fire() override; // Переопределяем функцию Fire

private:
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<ABossProjectile> BossProjectileClass;
};
