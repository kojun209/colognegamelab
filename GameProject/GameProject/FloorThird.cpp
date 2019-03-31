#include <iostream>

#include "FloorThird.h"

FloorThird::FloorThird()
{
}

FloorThird::~FloorThird()
{
}

void FloorThird::Initialize()
{
	mFloorNumber = eFloorNumber::THIRD;
}

void FloorThird::Run()
{
	Floor::Run();

	if (mKilledMonstersCount == THIRD_FLOOR_END)
	{
		cout << endl;
		cout << "You win. Game over." << endl;
		_getwch();
	}
}
