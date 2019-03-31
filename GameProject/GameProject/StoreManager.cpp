#include <iostream>

#include "StoreManager.h"
#include "StoreWeapon.h"
#include "StoreArmor.h"
#include "StoreCard.h"

using namespace std;

StoreManager* StoreManager::mInstance = nullptr;

StoreManager::~StoreManager()
{
	for (auto& store : mStores)
	{
		delete store;
	}
}

void StoreManager::Initialize()
{
	createStore(eStoreType::WEAPON);
	createStore(eStoreType::ARMOR);
	createStore(eStoreType::CARD);
}

void StoreManager::Run()
{
	while (true)
	{
		switch (outputMenu())
		{
		case WEAPON:
			mStores[eStoreType::WEAPON - 1]->Run();
			break;
		case ARMOR:
			mStores[eStoreType::ARMOR - 1]->Run();
			break;
		case CARD:
			mStores[eStoreType::CARD - 1]->Run();
			break;
		default:
			return;
		}
	}
}

void StoreManager::createStore(eStoreType storeType)
{
	Store* store = nullptr;

	switch (storeType)
	{
	case WEAPON:
		store = new StoreWeapon;
		break;
	case ARMOR:
		store = new StoreArmor;
		break;
	case CARD:
		store = new StoreCard;
		break;
	default:
		break;
	}

	store->Initialize();
	mStores.push_back(store);
}

int StoreManager::outputMenu()
{
	int input = 0;
	while (input < eStoreType::WEAPON || input > eStoreType::STORE_COUNT)
	{
		system("cls");
		cout << "1. Weapon Store" << endl;
		cout << "2. Armor Store" << endl;
		cout << "3. Card Store" << endl;
		cout << "4. Back" << endl;
		cout << "Select a store : ";

		input = _getwche() - 48;
	}

	return input;
}
