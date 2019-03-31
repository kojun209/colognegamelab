#pragma once

#include "Floor.h"

class FloorFirst final :
	public Floor
{
public:
	FloorFirst();
	virtual ~FloorFirst() override;

	virtual void Initialize();
	virtual void Run() override;
};

