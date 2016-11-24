#include "escapeTheRoom.h"
#include "escapeTheRoomBlueprintFunctionLibrary.h"


int32 nameIndex = 0;

/**
** Use TSubclassOf to garauntee that the desired class of the component to construct is actually a UActorComponent child class. Also, it helps Blueprints help you pick the correct UClass type - MH
**/
UActorComponent* UescapeTheRoomBlueprintFunctionLibrary::RequireComponent(AActor* IntendedOwner, TSubclassOf<UActorComponent> requiredComponentClass, bool &classFound)
{
	UActorComponent* ResultComponent = nullptr;
	UClass* ComponentClass = *requiredComponentClass;
	if(ComponentClass && IntendedOwner)
	{
		ResultComponent = IntendedOwner->FindComponentByClass(ComponentClass);
		/*if (ResultComponent)
		{
			UE_LOG(LogTemp, Warning, TEXT("Found First Component %s of Class %s in Actor %s"), *ResultComponent->GetName(), *ComponentClass->GetName(), *IntendedOwner->GetName());
		}
		else 
		{*/
			FName name = *ComponentClass->GetName();
			
			FString nameIncrementString = name.ToString();

			nameIncrementString.Append("_");
			nameIncrementString.Append(FString::FromInt(nameIndex));
			
			FName newCompName = FName(*nameIncrementString);

			nameIndex =nameIndex +1;

			#if WITH_EDITOR
			IntendedOwner->Modify();
			#endif
		    // Construct the new component and attach as needed
			UActorComponent* NewInstanceComponent = NewObject<UActorComponent>(IntendedOwner, ComponentClass, newCompName);
        	if(NewInstanceComponent)
        	{
				// Add to SerializedComponents array so it gets saved
				IntendedOwner->AddInstanceComponent(NewInstanceComponent);
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
	
	classFound = ResultComponent != nullptr;
	return ResultComponent;
}