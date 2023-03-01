// Fill out your copyright notice in the Description page of Project Settings.


#include "LazyActor.h"

#include "Components/SphereComponent.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "MeshLoadTest/MeshLoadTestCharacter.h"

// Sets default values
ALazyActor::ALazyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshLoadTriggerSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Mesh load trigger sphere"));
	MeshLoadTriggerSphere->OnComponentBeginOverlap.AddDynamic(this, &ALazyActor::OnSphereBeginOverlap);
	MeshLoadTriggerSphere->OnComponentEndOverlap.AddDynamic(this, &ALazyActor::OnSphereEndOverlap);
	SetRootComponent(MeshLoadTriggerSphere);
	
	ActorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Actor mesh"));
	ActorMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ALazyActor::BeginPlay()
{
	Super::BeginPlay();

	MeshLoadTriggerSphere->SetSphereRadius(MeshLoadRadius);
}

// Called every frame
void ALazyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALazyActor::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(!Cast<AMeshLoadTestCharacter>(OtherActor))
	{
		return;
	}

	if(MeshRef.IsPending())
	{
		FStreamableManager& StreamableManager = UAssetManager::Get().GetStreamableManager();
		MeshRef = Cast<UStaticMesh>(StreamableManager.LoadSynchronous(MeshRef.ToSoftObjectPath()));
	}

	ActorMesh->SetStaticMesh(MeshRef.Get());
}

void ALazyActor::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(!Cast<AMeshLoadTestCharacter>(OtherActor))
	{
		return;
	}
	
	ActorMesh->SetStaticMesh(nullptr);
	MeshRef.ResetWeakPtr();
}

