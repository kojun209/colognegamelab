#pragma once

#include "Floor.h"

class FloorThird final :
	public Floor
{
public:
	FloorThird();
	virtual ~FloorThird() override;

	virtual void Initialize();
	virtual void Run() override;
};

