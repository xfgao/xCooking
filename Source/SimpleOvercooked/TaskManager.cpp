// Fill out your copyright notice in the Description page of Project Settings.

#include "TaskManager.h"


// Sets default values
ATaskManager::ATaskManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	allTasks.Emplace(TEXT("Make lemon juice"));
	allTasks.Emplace(TEXT("Make sliced green apple"));

	ingredient2index.Add(TEXT("green apple"), 0);
	ingredient2index.Add(TEXT("red apple"), 1);

	currentTask = 0;
}

// Called when the game starts or when spawned
void ATaskManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATaskManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

