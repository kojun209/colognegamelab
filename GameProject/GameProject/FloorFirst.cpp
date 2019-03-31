#include <iostream>

#include "FloorFirst.h"

FloorFirst::FloorFirst()
{
}

FloorFirst::~FloorFirst()
{
}

void FloorFirst::Initialize()
{
	mFloorNumber = eFloorNumber::FIRST;
}

void FloorFirst::Run()
{
	Floor::Run();

	if (mKilledMonstersCount == FIRST_FLOOR_END)
	{
		cout << "The door to the second floor opened" << endl;	
		// ...
		_getwch();
	}
}