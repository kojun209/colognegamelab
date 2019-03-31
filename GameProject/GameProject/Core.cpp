#include <iostream>

#include "Core.h"
#include "FloorManager.h"
#include "ObjectManager.h"
#include "StoreManager.h"
#include "Inventory.h"

using namespace std;

Core* Core::mInstance = nullptr;

enum eMainMenu
{
	SPIRE = 1,
	STORE,
	INVENTORY,
	EXIT
};

Core::~Core()
{
	ObjectManager::DestroyInstance();
	FloorManager::DestroyInstance();
	StoreManager::DestroyInstance();
	Inventory::DestroyInstance();
}

void Core::Initialize()
{
	setLevelUpInfo();
	ObjectManager::GetInstance()->Initialize();
	FloorManager::GetInstance()->Initialize();
	StoreManager::GetInstance()->Initialize();
	Inventory::GetInstance()->Initialize();
}

void Core::Run()
{
	while (true)
	{
		switch (outputMainMenu())
		{
		case SPIRE:
			FloorManager::GetInstance()->Run();
			break;
		case STORE:
			StoreManager::GetInstance()->Run();
			break;
		case INVENTORY:
			Inventory::GetInstance()->Run();
			break;
		case EXIT:
			return;
		default:
			break;
		}
	}
}

int Core::outputMainMenu()
{
	int input = 0;
	while (input < eMainMenu::SPIRE || input > eMainMenu::EXIT)
	{
		system("cls");
		cout << "1. Tower" << endl;
		cout << "2. Store" << endl;
		cout << "3. Inventory" << endl;
		cout << "4. Exit" << endl;
		cout << "Select an option: ";

		input = _getwche() - 48;
	}

	return input;
}

void Core::setLevelUpInfo()
{
	mLevelUpInfo[eClassType::KNIGHT - 1] = createLevelUpInfo(10, 15, 100);
}

LevelUpInfo Core::GetLevelUpInfo(eClassType classType)
{
	return mLevelUpInfo[classType - 1];
}

LevelUpInfo Core::createLevelUpInfo(int attack, int defense, int hp)
{
	LevelUpInfo info = {};

	info.Attack = attack;
	info.Defense = defense;
	info.Hp = hp;

	return info;
}