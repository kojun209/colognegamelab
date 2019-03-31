#pragma once
#include "Floor.h"
class FloorSecond final :
	public Floor
{
public:
	FloorSecond();
	virtual ~FloorSecond() override;

	virtual void Initialize();
	virtual void Run() override;
};

