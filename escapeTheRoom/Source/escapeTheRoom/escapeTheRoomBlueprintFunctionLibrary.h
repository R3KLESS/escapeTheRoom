#pragma once

#include "Components/ActorComponent.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "escapeTheRoomBlueprintFunctionLibrary.generated.h"

UCLASS()
class ESCAPETHEROOM_API UescapeTheRoomBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
    
public:
    /**Dynamically create a UActorComponent on a given actor during runtime or outside of the constructor.**/
    UFUNCTION(BlueprintCallable, Category="CustomBpNodes|Component")
    static UActorComponent* RequireComponent(AActor* IntendedComponentOwner,
		TSubclassOf<UActorComponent> requiredComponentClass);

    /**This templated function is not available for use in blueprints but makes for a nice helper in C++**/
    template<typename T>
    FORCEINLINE static T* RequireComponentCast(AActor* IntendedComponentOwner) { return Cast<T>(RequireComponent(IntendedOwner, T::StaticClass())); }

};