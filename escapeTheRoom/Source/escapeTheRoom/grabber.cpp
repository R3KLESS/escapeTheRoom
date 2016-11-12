// Fill out your copyright notice in the Description page of Project Settings.

#include "escapeTheRoom.h"
#include "grabber.h"

#define OUT


// Sets default values for this component's properties
Ugrabber::Ugrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void Ugrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void Ugrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	OUT FVector playerViewPoint;
	OUT FRotator playerViewPointRotation;

	// get the players viewpoint
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(playerViewPoint, playerViewPointRotation);

	// raycast out to reach distance

	// see what we hit

	// log out to test
	UE_LOG(LogTemp, Warning, TEXT ("players viewpoint is %s , players rotation is %s"), 
		*playerViewPoint.ToString(), 
		*playerViewPointRotation.ToString())
}

