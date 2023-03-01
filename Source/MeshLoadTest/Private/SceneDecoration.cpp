// Fill out your copyright notice in the Description page of Project Settings.


#include "SceneDecoration.h"

#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"

// Sets default values
ASceneDecoration::ASceneDecoration()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Scene root"));
	SetRootComponent(SceneRoot);
	ActorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Decoration Mesh"));
	ActorMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASceneDecoration::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASceneDecoration::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASceneDecoration::LoadResources()
{
	FStreamableManager& StreamableManager = UAssetManager::Get().GetStreamableManager();

	if(MeshRef.IsPending())
	{
		MeshRef = Cast<UStaticMesh>(StreamableManager.LoadSynchronous(MeshRef.ToSoftObjectPath()));
	}

	if(MaterialRef.IsPending())
	{
		MaterialRef = Cast<UStaticMesh>(StreamableManager.LoadSynchronous(MaterialRef.ToSoftObjectPath()));
	}

	if(MeshRef.IsValid())
	{
		ActorMesh->SetStaticMesh(MeshRef.Get());
	}

	if(MaterialRef.IsValid())
		ActorMesh->SetMaterial(0, MaterialRef.Get());
}

