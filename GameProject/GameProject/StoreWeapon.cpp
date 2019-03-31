#include <iostream>
#include <fstream>

#include "StoreWeapon.h"
#include "ItemWeapon.h"
#include "Player.h"
#include "ObjectManager.h"
#include "Inventory.h"

using namespace std;

void StoreWeapon::Initialize()
{
	ifstream fin("StoreWeapon.swp", ios_base::in | ios_base::binary);

	if (fin.is_open())
	{
		unsigned int weaponsCount = 0;

		fin.read((char*)&weaponsCount, sizeof(unsigned int));

		for (size_t i = 0; i < weaponsCount; i++)
		{
			Item* item = new ItemWeapon(eObjectType::WEAPON);
			item->Initialize();

			item->Load(fin);
			mItems.push_back(item);
		}
	}
}

void StoreWeapon::Run()
{
	Player* player = static_cast<Player*>(ObjectManager::GetInstance()->GetObject("Player"));

	while (true)
	{
		system("cls");
		cout << "===================== WEAPON STORE =====================" << endl;
		outputItemList();

		unsigned int back = mItems.size() + 1;
		cout << back << ". Back" << endl;
		cout << endl;
		cout << "Gold : " << player->GetGold() << endl;
		cout << "Select an item : ";

		unsigned int input = _getwche() - 48;
		if (input == 0 || input > back)
		{
			continue;
		}

		if (input == back)
		{
			return;
		}

		cout << endl << endl;

		if (Inventory::GetInstance()->IsFull())
		{
			cout << "Inventory is full" << endl;
			_getwch();
			continue;
		}

		if (player->GetGold() < mItems[input - 1]->GetItemInfo().PriceToBuy)
		{
			cout << "Not enough Gold" << endl;
			_getwch();
			continue;
		}

		Item* item = mItems[input - 1]->Clone();

		Inventory::GetInstance()->AddItem(item);
		player->AddGold(-item->GetItemInfo().PriceToBuy);

		cout << "Bought " << item->GetName();
		_getwch();
	}
}

StoreWeapon::StoreWeapon()
{
}

StoreWeapon::~StoreWeapon()
{
}
