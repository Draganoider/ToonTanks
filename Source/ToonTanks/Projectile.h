// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"


UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat1", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ProjectileMesh;

    UPROPERTY(VisibleAnywhere, category = "Combat1")
	class UProjectileMovementComponent* ProjectileMovement;

	

	UPROPERTY(EditAnywhere)
	float Damage = 50.f;

	UPROPERTY(EditAnywhere, Category = "Combat1")
	class UParticleSystem* HitParticles;

    UPROPERTY(VisibleAnywhere, Category = "Combat1")
	class UParticleSystemComponent* TrailParticle;

	UPROPERTY(EditAnywhere, Category = "Combat1")
	class USoundBase* LaunchSound;

	UPROPERTY(EditAnywhere, Category = "Combat1")
	USoundBase* HitSound;

	UPROPERTY(EditAnywhere, Category = "Combat1")
	TSubclassOf<class UCameraShakeBase> HitCameraShakeClass;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;






    

	
};
