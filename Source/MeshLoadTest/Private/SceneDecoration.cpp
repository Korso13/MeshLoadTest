// Fill out your copyright notice in the Description page of Project Settings.


#include "SceneDecoration.h"

#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "Kismet/KismetSystemLibrary.h"

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

void ASceneDecoration::LoadResourcesAsync(double Time)
{
	ExecutionStartTime = Time;
	LocalExecStartTime = FPlatformTime::Seconds();

	FStreamableDelegate StreamableDelegateMesh;
	FStreamableDelegate StreamableDelegateMaterial;
	StreamableDelegateMesh.BindUObject(this, &ASceneDecoration::OnResourcesLoaded, &MeshLoadHandler);
	StreamableDelegateMaterial.BindUObject(this, &ASceneDecoration::OnResourcesLoaded, &MaterialLoadHandler);

	FStreamableManager& StreamableManager = UAssetManager::Get().GetStreamableManager();
	MeshLoadHandler = StreamableManager.RequestAsyncLoad(MeshRef.ToSoftObjectPath(), StreamableDelegateMesh);
	MaterialLoadHandler = StreamableManager.RequestAsyncLoad(MaterialRef.ToSoftObjectPath(), StreamableDelegateMaterial);
}

void ASceneDecoration::OnResourcesLoaded(TSharedPtr<FStreamableHandle>* LoadedAsset)
{
	UStaticMesh* Mesh = Cast<UStaticMesh>(LoadedAsset->Get()->GetLoadedAsset());
	UMaterial* Material = Cast<UMaterial>(LoadedAsset->Get()->GetLoadedAsset());
	if(Mesh)
	{
		ActorMesh->SetStaticMesh(Mesh);
	}
	else if(Material)
	{
		ActorMesh->SetMaterial(0, Material);
	}
	FString TimeElapsed;
	TimeElapsed = FString::Printf(TEXT("%s loaded its resources in %f seconds, and %f seconds after start of startup resource load."), *GetName(), ((FPlatformTime::Seconds() - LocalExecStartTime)), (FPlatformTime::Seconds() - ExecutionStartTime));
	UE_LOG(LogTemp, Warning, TEXT("%s loaded its resources in %f seconds, and %f seconds after start of startup resource load."), *GetName(), ((FPlatformTime::Seconds() - LocalExecStartTime)), (FPlatformTime::Seconds() - ExecutionStartTime));
	UKismetSystemLibrary::PrintString(this, TimeElapsed);
}

