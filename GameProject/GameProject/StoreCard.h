#pragma once

#include "Store.h"

class StoreCard final :
	public Store
{
	friend class StoreManager;

public:
	virtual void Initialize() override;
	virtual void Run() override;

private:
	StoreCard();
	virtual ~StoreCard();
};

