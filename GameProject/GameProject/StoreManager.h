#pragma once

#include <vector>

#include "Singleton.h"

enum eStoreType
{
	WEAPON = 1,
	ARMOR,
	CARD,
	STORE_COUNT
};

class Store;

class StoreManager
{
public:
	DECLARE_SINGLETON(StoreManager)

	void Initialize();
	void Run();

private:
	void createStore(eStoreType storeType);
	int outputMenu();

private:
	std::vector<Store*> mStores;
};
