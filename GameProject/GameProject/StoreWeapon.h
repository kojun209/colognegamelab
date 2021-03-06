#pragma once

#include "Store.h"

class StoreWeapon final :
	public Store
{
	friend class StoreManager;

public:
	virtual void Initialize() override;
	virtual void Run() override;

private:
	StoreWeapon();
	virtual ~StoreWeapon();
};

