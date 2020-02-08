// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "OpenDoor.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	//Find the owning Actor
	Owner = GetOwner();

	if (PressurePlatePurple == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing Pressure Plate"), *GetOwner()->GetName());
	}
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the trigger volume
	if (RoomNumber == 1)
	{
		if (GetTotalMassOfActorsOnPlate() > TriggerMass)
		{
			OnOpen.Broadcast();
		}

		// Check if it's time to close the door
		else
		{
			OnClose.Broadcast();
		}
	}
	if (RoomNumber == 2)
	{
		if (CheckBothPlatesAreCovered() == true)
		{
			OnOpen.Broadcast();
		}

		// Check if it's time to close the door
		else
		{
			OnClose.Broadcast();
		}
	}
	if (RoomNumber == 3)
	{
		if (GetTotalMassOfActorsOnPlate() > TriggerMass)
		{
			OnOpen2.Broadcast();
		}
		else
		{
			OnClose2.Broadcast();
		}
		if (CheckCorrectObjectOnPlate(GreenChair) && GetTotalMassOfActorsOnPlate() > TriggerMass)
		{
			OnOpen.Broadcast();
		}
		else
		{
			OnClose.Broadcast();
		}
	}

	//UE_LOG(LogTemp, Warning, TEXT("%f"), GetTotalMassOfActorsOnPlate());
}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.f;

	// find all overlapping actors
	TArray<AActor *> OverlappingActors;
	if (PressurePlatePurple == nullptr)
	{
		return TotalMass;
	}
	PressurePlatePurple->GetOverlappingActors(OUT OverlappingActors);

	// iterate through them adding their masses
	for (const auto *Actor : OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		//UE_LOG(LogTemp, Warning, TEXT("%s on pressure plate"), *Actor->GetName());
	}

	return TotalMass;
}

bool UOpenDoor::CheckBothPlatesAreCovered()
{
	// find all overlapping actors
	TArray<AActor *> OverlappingActorsPurple;
	TArray<AActor *> OverlappingActorsGreen;
	bool PurpleOnPurple = false;
	bool GreenOnGreen = false;
	if (PressurePlatePurple == nullptr || PressurePlateGreen == nullptr || PurpleTable == nullptr || GreenChair == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has a nullptr"), *GetOwner()->GetName());
		return false;
	}
	PressurePlatePurple->GetOverlappingActors(OUT OverlappingActorsPurple);
	PressurePlateGreen->GetOverlappingActors(OUT OverlappingActorsGreen);
	for (const auto *Actor : OverlappingActorsPurple)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s on pressure plate"), *Actor->GetName());
		if (Actor->GetName() == PurpleTable->GetName() || Actor->GetName() == "DefaultPawn_BP_C_0")
		{
			PurpleOnPurple = true;
			UE_LOG(LogTemp, Warning, TEXT("Purple true"));
		}
		else
		{
			PurpleOnPurple = false;
		}
	}
	for (const auto *Actor : OverlappingActorsGreen)
	{
		if (Actor->GetName() == GreenChair->GetName() || Actor->GetName() == "DefaultPawn_BP_C_0")
		{
			GreenOnGreen = true;
		}
		else
		{
			GreenOnGreen = false;
		}
	}
	if (GreenOnGreen == true && PurpleOnPurple == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool UOpenDoor::CheckCorrectObjectOnPlate(AActor *DesiredObject)
{
	if (PressurePlatePurple == nullptr || PressurePlateGreen == nullptr || PurpleTable == nullptr || GreenChair == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has a nullptr"), *GetOwner()->GetName());
		return false;
	}
	TArray<AActor *> OverlappingActorsGreen;
	PressurePlateGreen->GetOverlappingActors(OUT OverlappingActorsGreen);
	for (const auto *Actor : OverlappingActorsGreen)
	{
		if (Actor->GetName() == DesiredObject->GetName())
		{
			return true;
		}
	}
	return false;
}