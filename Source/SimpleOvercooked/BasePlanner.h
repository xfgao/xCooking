#pragma once
#include "CoreMinimal.h"

class SIMPLEOVERCOOKED_API BasePlanner
{
	

	public:

	BasePlanner() {};
	TArray<FString> output_planner;
	virtual ~BasePlanner() = 0;
};



