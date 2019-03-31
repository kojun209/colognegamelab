#include <iostream>

#include "Inventory.h"
#include "Item.h"
#include "Player.h"
#include "ObjectManager.h"
#include "EEquippedItemType.h"

using namespace std;

enum eInventoryMenu
{
	EQUIP = 1,
	UPGRADE,
	BACK
};

enum eUpgradeMenu
{
	EXECUTE = 1,
	CANCEL
};
Inventory* Inventory::mInstance = nullptr;

Inventory::~Inventory()
{
	for (auto& item : mItems)
	{
		delete item;
	}
}

void Inventory::Initialize()
{
	mCapacity = 10;
}

void Inventory::Run()
{
	Player* player = static_cast<Player*>(ObjectManager::GetInstance()->GetObject("Player"));

	while (true)
	{
		int input = 0;
		while (input < eInventoryMenu::EQUIP || input > eInventoryMenu::BACK)
		{
			system("cls");
			cout << "===================== Inventory =====================" << endl;
			cout << "1. Equip" << endl;
			cout << "2. Upgrade" << endl;
			cout << "3. Back" << endl;
			cout << "Select an option : ";
			input = _getwche() - 48;
		}

		if (input == eInventoryMenu::BACK)
		{
			return;
		}

		if (input == eInventoryMenu::EQUIP)
		{
			while (true)
			{
				int input = 0;
				while(input < 1 || input > static_cast<int>(mItems.size() + 3))
				{
					system("cls");
					cout << "===================== EQUIP =====================" << endl;
					player->Render();
					cout << endl;

					size_t i = 0;
					for (i = 0; i < mItems.size(); i++)
					{
						cout << i + 1 << ". ";
						mItems[i]->Render();
						cout << endl;
					}

					cout << i + 1<< ". Unequip weapon" << endl;
					cout << endl;
					cout << i + 2 << ". Unequip armor" << endl;
					cout << endl;

					cout << i + 3 << ". Back" << endl;
					cout << "Select an item to equip : ";
					input = _getwche() - 48;
				}

				if (input == mItems.size() + 3)
				{
					break;
				}

				cout << endl;
				cout << endl;

				if (input == mItems.size() + 1 && !player->mItems[eEquippedItemType::EQ_WEAPON])
				{
					cout << "There is no equipped weapon";
				}
				else if (input == mItems.size() + 2 && !player->mItems[eEquippedItemType::EQ_ARMOR])
				{
					cout << "There is no equipped armor";
				}
				else if (input == mItems.size() + 1)
				{
					ItemWeapon* weapon = static_cast<ItemWeapon*>(player->mItems[eEquippedItemType::EQ_WEAPON]);
					mItems.push_back(weapon);

					cout << "Unequipped " << weapon->GetName();

					player->mItems[eEquippedItemType::EQ_WEAPON] = 0;
				}
				else if (input == mItems.size() + 2)
				{
					ItemArmor* armor = static_cast<ItemArmor*>(player->mItems[eEquippedItemType::EQ_ARMOR]);
					mItems.push_back(armor);	// unequip item and move it to the Inventory

					cout << "Unequipped " << armor->GetName();

					player->mItems[eEquippedItemType::EQ_ARMOR] = 0;
				}
				else
				{
					Item* equippedItem = player->EquipItemOrNull(mItems[input - 1]);

					cout << "Equipped " << mItems[input - 1]->GetName();

					if (equippedItem)	// replace the item
					{
						mItems[input - 1] = equippedItem;
					}
					else	// delete the item
					{
						vector<Item*>::iterator it = mItems.begin() + (input - 1);
						mItems.erase(it);
					}
				}
				_getwch();
			}
		}

		if (input == eInventoryMenu::UPGRADE)
		{
			while (true)
			{
				int item = 0;
				while (item < 1 || item > static_cast<int>(mItems.size() + 1))
				{
					system("cls");
					cout << "===================== UPGRADE =====================" << endl;

					for (size_t i = 0; i < mItems.size(); i++)
					{
						cout << i + 1 << ". ";
						mItems[i]->Render();
						cout << endl;
					}

					cout << mItems.size() + 1 << ". Back" << endl;
					cout << "Select an item to upgrade : ";
					item = _getwche() - 48;
				}

				if (item == mItems.size() + 1)
				{
					break;
				}

				cout << endl;
				cout << endl;

				int currentUpgradeLevel = mItems[item - 1]->mUpgradeLevel;
				if (currentUpgradeLevel >= 10)
				{
					cout << "Maximum upgrade" << endl;
					break;
				}
				
			
				int cost = static_cast<int>(mItems[item - 1]->GetItemInfo().PriceToBuy * (currentUpgradeLevel + 1));
				int successProbability = 100 - 10 * currentUpgradeLevel;
				int playerGold = player->GetGold();
				
				cout << "The item ability will be increased by " << 10 * (currentUpgradeLevel + 1) << "% of the current ability" << endl;
				// ...
				cout << "Success probability : " << successProbability << "%" << "\tCost : " << cost << " gold" << endl;

				cout << "Gold : " << playerGold << endl;
				cout << endl;
				cout << "1. Upgrade" << endl;
				cout << "2. Cancel" << endl;
				cout << "Select an option : ";

				input = 0;
				while (input < eUpgradeMenu::EXECUTE || input > eUpgradeMenu::CANCEL)
				{
					input = _getwch() - 48;
				}

				cout << input;
				if (input == eUpgradeMenu::CANCEL)
				{
					continue;
				}

				cout << endl << endl;
				if (playerGold < cost)
				{
					cout << "Not enough Gold" << endl;
					_getwch();
					continue;
				}

				if (rand() % 10000 / 100.f < successProbability)
				{
					mItems[item - 1]->mUpgradeLevel++;
					cout << "Upgrade succeeded!" << endl;
				}
				/// ...
				else
				{
					cout << "Upgrade failed" << endl;
				}

				_getwch();
				player->AddGold(-cost);
			}
		}
	}
}