#include "MovingWall.h"

// Sets default values
AMovingWall::AMovingWall()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallMesh"));
	RootComponent = WallMesh;

	StartLocation = FVector(0.0f, 0.0f, 0.0f);
	EndLocation = FVector(0.0f, 0.0f, 0.0f);
	Offset = FVector(0.0f, 0.0f, 0.0f);
	Duration = 5.0f;
	CurrentTime = 0.0f;
	bMovingForward = true; // Инициализация новой переменной
}

// Called when the game starts or when spawned
void AMovingWall::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();
	EndLocation = StartLocation + Offset;
}

// Called every frame
void AMovingWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentTime += DeltaTime;

	if (CurrentTime > Duration)
	{
		CurrentTime = 0.0f;
		bMovingForward = !bMovingForward; // Реверс направления
	}

	// Calculate the interpolation factor
	float Alpha = CurrentTime / Duration;

	// Interpolate between the start and end locations based on the direction
	FVector NewLocation = bMovingForward ? FMath::Lerp(StartLocation, EndLocation, Alpha) : FMath::Lerp(EndLocation, StartLocation, Alpha);

	// Set the new location
	SetActorLocation(NewLocation);
}
