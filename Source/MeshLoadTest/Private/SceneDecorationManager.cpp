// Fill out your copyright notice in the Description page of Project Settings.


#include "SceneDecorationManager.h"

#include "SceneDecoration.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASceneDecorationManager::ASceneDecorationManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASceneDecorationManager::BeginPlay()
{
	Super::BeginPlay();
	
	double start = FPlatformTime::Seconds();
	
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASceneDecoration::StaticClass(), FoundActors);

	if(FoundActors.Num() == 0)
	{
		return;
	}
	
	for(const auto& Actor : FoundActors)
	{
		ASceneDecoration* Decoration = Cast<ASceneDecoration>(Actor);
		if(Decoration)
		{
			Decoration->LoadResourcesAsync(start);
		}
	}

	double end = FPlatformTime::Seconds();
	FString TimeElapsed;
	TimeElapsed = FString::Printf(TEXT("Scene manager code executed in %f seconds"), (end - start));

	UE_LOG(LogTemp, Warning, TEXT("Scene manager code executed in %f seconds."), (end - start));
	UKismetSystemLibrary::PrintString(this, TimeElapsed);

}

// Called every frame
void ASceneDecorationManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

