#pragma once

#include "Store.h"

class StoreArmor final :
	public Store
{
	friend class StoreManager;

public:
	virtual void Initialize() override;
	virtual void Run() override;

private:
	StoreArmor();
	virtual ~StoreArmor();
};

