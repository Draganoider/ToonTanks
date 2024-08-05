#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "GameFramework/Actor.h"
#include "BossProjectile.generated.h"

class ATank;

UCLASS()
class TOONTANKS_API ABossProjectile : public AProjectile
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABossProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	void SetHomingTarget(AActor *Target);

	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category = "Combat")
	bool bIsHomingProjectile = true;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float HomingAccelerationMagnitude = 5000.0f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float HomingDuration = 2.0f; // Продолжительность наведения в секундах

	void FindHomingTarget();
	void StopHoming();

	AActor *HomingTarget;

	FTimerHandle HomingTimerHandle; // Таймер для остановки наведения
};
