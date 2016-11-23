// Fill out your copyright notice in the Description page of Project Settings.

#include "escapeTheRoom.h"
#include "grabber.h"
#include "escapeTheRoomBlueprintFunctionLibrary.h"

#define OUT


// Sets default values for this component's properties
Ugrabber::Ugrabber()// :
//	createdPhysicsHandleComponent(nullptr)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

//void Ugrabber::PostInitProperties()
//{
//	Super::PostInitProperties();
//	//This initializes stuff C++ side outside of the constructor but allows us to edit it in the Editor
//	if(createdPhysicsHandleComponent == nullptr)
//	{
//		bool bFound = false;
//		createdPhysicsHandleComponent = UescapeTheRoomBlueprintFunctionLibrary::RequireComponentCast<UPhysicsHandleComponent>(GetOwner(), bFound);
//		if(bFound)
//		{
//			//Do Stuff here;
//		}
//	}
//}

// Called when the game starts
void Ugrabber::BeginPlay()
{
	Super::BeginPlay();
	
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