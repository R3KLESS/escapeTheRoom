#include "escapeTheRoom.h"
#include "escapeTheRoomBlueprintFunctionLibrary.h"

/**
** Use TSubclassOf to garauntee that the desired class of the component to construct is actually a UActorComponent child class. Also, it helps Blueprints help you pick the correct UClass type - MH
**/
UActorComponent* RequireComponent(AActor* IntendedOwner, TSubclassOf<UActorComponent> testClass, bool &classFound);
{
	UActorComponent* ResultComponent = nullptr;
	UClass* ComponentClass = *testClass;
	if(ComponentClass && IntendedOwner)
	{
		if (ResultComponent = IntendedOwner->FindComponentByClass(ComponentClass))
		{
			UE_LOG(LogTemp, Warning, TEXT("Found First Component %s of Class %s in Actor %s"), *ResultComponent->GetName(), *ComponentClass->GetName(), *IntendedOwner->GetName());
		}
		else
		{
			#if WITH_EDITOR
			IntendedOwner->Modify();
			#endif
		    // Construct the new component and attach as needed
			UActorComponent* NewInstanceComponent = NewObject<UActorComponent>(IntendedOwner, ComponentClass, TEXT("DynamicComponentInstance"));
        	if(NewInstanceComponent)
        	{
				// Add to SerializedComponents array so it gets saved
				AddInstanceComponent(NewInstanceComponent);
                // Fire off the event that a Component was created
				NewInstanceComponent->OnComponentCreated();
                // Register the Component so that it is active in game code
				NewInstanceComponent->RegisterComponent();

				#if WITH_EDITOR
				IntendedOwner->RerunConstructionScripts();
				#endif

				ResultComponent = NewInstanceComponent;

				UE_LOG(LogTemp, Log, TEXT("Created required Component %s of type %s on Actor %s"), *ResultComponent->GetName(), *ResultComponent->GetClass()->GetName(), *IntendedOwner->GetName());
			}
		}
	}
	classFound = ResultComponent != nullptr;
	return ResultComponent;
}