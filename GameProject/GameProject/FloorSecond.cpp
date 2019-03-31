#include <iostream>

#include "FloorSecond.h"

FloorSecond::FloorSecond()
{
}

FloorSecond::~FloorSecond()
{
}

void FloorSecond::Initialize()
{
	mFloorNumber = eFloorNumber::SECOND;
}

void FloorSecond::Run()
{
	Floor::Run();

	if (mKilledMonstersCount == SECOND_FLOOR_END)
	{
		cout << endl;
		cout << "The door to the third floor opened" << endl;
		_getwch();
	}
}
