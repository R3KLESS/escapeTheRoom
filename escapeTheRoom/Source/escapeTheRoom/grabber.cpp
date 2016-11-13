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

	// look for attached physics handle
	physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (physicsHandle)
	{

	}
	else
	{
		
		UE_LOG(LogTemp, Warning, TEXT(" %s is missing physics handle component, please attach a physics handle component and try again!!"), *GetOwner()->GetName())
	}
	
}


// Called every frame
void Ugrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	OUT FVector playerViewPoint;
	OUT FRotator playerViewPointRotation;

	// get the players viewpoint
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(playerViewPoint, playerViewPointRotation);

	// draw a debug line in the world to visualise the grabber reach

	FVector lineTraceEnd = playerViewPoint + playerViewPointRotation.Vector() * grabberReach;

	DrawDebugLine(GetWorld(), playerViewPoint, lineTraceEnd, FColor(255, 0, 0), false, 0.f, 0.f, 10.f);
	
	// set up query parameters
	FCollisionQueryParams traceParameters (FName(TEXT("")), false, GetOwner());
	 
	// line trace/raycast out to reach distance
	FHitResult hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT hit, 
		playerViewPoint, 
		lineTraceEnd, 
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		traceParameters);

	// see what we hit
	AActor* actorHit = hit.GetActor();
	if (actorHit)
		{
			UE_LOG(LogTemp, Warning, TEXT("the actor that was hit is %s"), *actorHit->GetName())
		}

	//// log out to test

	

	//UE_LOG(LogTemp, Warning, TEXT ("players viewpoint is %s , players rotation is %s"), 
	//	*playerViewPoint.ToString(), 
	//	*playerViewPointRotation.ToString())

}

