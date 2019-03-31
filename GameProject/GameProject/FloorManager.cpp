#include <iostream>

#include "FloorManager.h"
#include "FloorFirst.h"
#include "FloorSecond.h"
#include "FloorThird.h"
#include "EMonsterClass.h"
#include "EFloorEnd.h"

using namespace std;

FloorManager* FloorManager::mInstance = nullptr;

FloorManager::~FloorManager()
{
	for (auto& floor : mFloors)
	{
		delete floor;
	}
}

void FloorManager::Initialize()
{
	createStage(eFloorNumber::FIRST);
	createStage(eFloorNumber::SECOND);
	createStage(eFloorNumber::THIRD);
}

void FloorManager::Run()
{
	int killedMonstersCount = Floor::GetKilledMonstersCount();

	if (killedMonstersCount < FIRST_FLOOR_END)
	{
		mFloors[eFloorNumber::FIRST - 1]->Run();
	}
	// ...
	else if (killedMonstersCount < SECOND_FLOOR_END)
	{
		mFloors[eFloorNumber::SECOND - 1]->Run();
	}
	else
	{
		mFloors[eFloorNumber::THIRD - 1]->Run();
	}
}

void FloorManager::createStage(eFloorNumber floorNumber)
{
	Floor* floor = nullptr;

	switch (floorNumber)
	{
	case FIRST:
		floor = new FloorFirst;
		break;
	case SECOND:
		floor = new FloorSecond;
		break;
	case THIRD:
		floor = new FloorThird;
		break;
	default:
		break;
	}

	floor->Initialize();
	mFloors.push_back(floor);
}