#pragma once

#include <vector>

#include "Singleton.h"
#include "EFloorNumber.h"

class FloorManager
{
public:
	DECLARE_SINGLETON(FloorManager)

	void Initialize();
	void Run();
	
private:
	void createStage(eFloorNumber floorNumber);

private:
	std::vector<class Floor*> mFloors;
};