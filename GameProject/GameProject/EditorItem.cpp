#include <iostream>
#include <fstream>

#include "EditorItem.h"
#include "ItemWeapon.h"
#include "ItemArmor.h"
#include "EItemType.h"
#include "EWeaponOption.h"

using namespace std;

EditorItem* EditorItem::mInstance = nullptr;

enum eEditItemMenu
{
	ADD = 1,
	DELETE,
	LIST,
	SAVE,
	LOAD,
	BACK
};

EditorItem::~EditorItem()
{
	for (auto& weapon : mWeapons)
	{
		delete weapon;
	}

	for (auto& armor : mArmors)
	{
		delete armor;
	}
}

void EditorItem::Initialize()
{
}

void EditorItem::Run()
{
	while (true)
	{
		switch (outputMenu())
		{
		case ADD:
			add();
			break;
		case DELETE:
			remove();
			break;
		case LIST:
			list();
			break;
		case SAVE:
			save();
			break;
		case LOAD:
			load();
			break;
		case BACK:
			return;
		default:
			break;
		}
	}
}

int EditorItem::outputMenu()
{
	int input = 0;
	while (input < eEditItemMenu::ADD || input > eEditItemMenu::BACK)
	{
		system("cls");
		cout << "===================== ITEM EDITOR =====================" << endl;
		cout << "1. Add" << endl;
		cout << "2. Delete" << endl;
		cout << "3. List" << endl;
		cout << "4. Save" << endl;
		cout << "5. Load" << endl;
		cout << "6. Back" << endl;
		cout << "Select an option : ";

		input = _getwche() - 48;
	}

	return input;
}

void EditorItem::add()
{
	int input = 0;
	while (input < eItemType::WEAPON || input > eItemType::COUNT)
	{
		system("cls");
		cout << "===================== Add =====================" << endl;
		cout << "1. Weapon" << endl;
		cout << "2. Armor" << endl;
		cout << "3. Back" << endl;
		cout << "Select an item type : ";

		input = _getwche() - 48;
	}

	if (input == eItemType::COUNT)
	{
		return;
	}

	system("cls");

	Item* item = nullptr;

	switch (input)
	{
	case eItemType::WEAPON:
		item = new ItemWeapon(eObjectType::WEAPON);
		cout << "===================== ADD WEAPON =====================" << endl;
		break;
	case eItemType::ARMOR:
		item = new ItemArmor(eObjectType::ARMOR);
		cout << "===================== ADD ARMOR =====================" << endl;
		break;
	default:
		break;
	}

	item->Initialize();

	cout << "Name : ";

	constexpr int NAME_SIZE = 32;
	char name[NAME_SIZE];
	cin.getline(name, NAME_SIZE);
	item->SetName(name);

	int priceToBuy, priceToSell;
	inputInt("Price to buy", priceToBuy);
	inputInt("Price to sell", priceToSell);

	cout << "Description : ";
	constexpr int DESCRIPTION_SIZE = 128;
	char description[DESCRIPTION_SIZE] = {};
	cin.getline(description, DESCRIPTION_SIZE);

	item->SetItemInfo(static_cast<eItemType>(input), priceToBuy, priceToSell, description);

	switch (input)
	{
	case eItemType::WEAPON:
	{
		int attack;
		inputInt("Attack", attack);

		cout << "Item option" << endl;
		cout << "1. None" << endl;
		cout << "2. Ignore defense" << endl;
		cout << "Select an option : ";

		int weaponOption = 0;
		while (weaponOption < eWeaponOption::WO_NONE || weaponOption >eWeaponOption::IGNORE_DEFENSE)
		{
			weaponOption = _getwch() - 48;
		}
		cout << weaponOption << endl;

		float value;
		inputFloat("Value", value);

		cout << "Option Description : ";
		constexpr int DESCRIPTION_SIZE = 128;
		char description[DESCRIPTION_SIZE] = {};
		cin.getline(description, DESCRIPTION_SIZE);

		static_cast<ItemWeapon*>(item)->SetAttack(attack);
		static_cast<ItemWeapon*>(item)->SetWeaponOption(static_cast<eWeaponOption>(weaponOption), value, description);
	}
		break;
	case eItemType::ARMOR:
	{
		int defense;
		inputInt("Defense", defense);

		cout << "Item option" << endl;
		cout << "1. None" << endl;
		cout << "2. Thorn" << endl;
		cout << "Select an option : ";

		int armorOption = 0;
		while (armorOption < eArmorOption::AO_NONE || armorOption >eArmorOption::THORN)
		{
			armorOption = _getwche() - 48;
		}
		cout << endl;

		float value;
		inputFloat("Value", value);

		cout << "Option Description : ";
		constexpr int DESCRIPTION_SIZE = 128;
		char description[DESCRIPTION_SIZE] = {};
		cin.getline(description, DESCRIPTION_SIZE);

		static_cast<ItemArmor*>(item)->SetDefense(defense);
		static_cast<ItemArmor*>(item)->SetArmorOption(static_cast<eArmorOption>(armorOption), value, description);
	}
		break;
	default:
		break;
	}

	switch (input)
	{
	case eItemType::WEAPON:
		mWeapons.push_back(item);
		break;
	case eItemType::ARMOR:
		mArmors.push_back(item);
		break;
	default:
		break;
	}

	cout << endl << "Added successfully";
	_getwch();
}

void EditorItem::remove()
{
	int input = 0;
	while (input < eItemType::WEAPON || input > eItemType::COUNT)
	{
		system("cls");
		cout << "===================== DELETE =====================" << endl;
		cout << "1. Weapon" << endl;
		cout << "2. Armor" << endl;
		cout << "3. Back" << endl;
		cout << "Select an item type : ";

		input = _getwche() - 48;
	}

	if (input == eItemType::COUNT)
	{
		return;
	}

	if (input == eItemType::WEAPON)
	{
		while (true)
		{
			system("cls");
			cout << "===================== DELETE WEAPON =====================" << endl;
			size_t i;
			for (i = 0; i < mWeapons.size(); i++)
			{
				cout << i + 1 << ". ";
				mWeapons[i]->Render();
				cout << endl;
			}

			cout << i + 1 << ". Back" << endl;
			cout << "Select a number to delete : ";

			unsigned int input = 0;
			while (input == 0 || input > mWeapons.size() + 1)
			{
				input = _getwch() - 48;
			}

			if (input == mWeapons.size() + 1)
			{
				return;
			}

			cout << input;

			vector<Item*>::iterator it;
			it = mWeapons.begin();

			it += (input - 1);
			mWeapons.erase(it);

			cout << endl << endl << "Deleted successfully";
			_getwche();
		}
	}
	else
	{
		while (true)
		{
			system("cls");
			cout << "===================== DELETE ARMOR =====================" << endl;
			size_t i;
			for (i = 0; i < mArmors.size(); i++)
			{
				cout << i + 1 << ". ";
				mArmors[i]->Render();
				cout << endl;
			}

			cout << i + 1 << ". Back" << endl;
			cout << "Select a number to delete : ";

			unsigned int input = 0;
			while (input == 0 || input > mArmors.size() + 1)
			{
				input = _getwch() - 48;
			}

			if (input == mArmors.size() + 1)
			{
				return;
			}

			cout << input;

			vector<Item*>::iterator it;
			it = mArmors.begin();

			it += (input - 1);
			mArmors.erase(it);

			cout << endl << endl << "Deleted successfully";
			_getwche();
		}
	}
}

void EditorItem::list()
{
	system("cls");
	cout << "===================== Weapon =====================" << endl;
	for (size_t i = 0; i < mWeapons.size(); i++)
	{
		cout << i + 1 << ". ";
		mWeapons[i]->Render();
		cout << endl;
	}

	cout << "===================== Armor =====================" << endl;
	for (size_t i = 0; i < mArmors.size(); i++)
	{
		cout << i + 1 << ". ";
		mArmors[i]->Render();
		cout << endl;
	}

	_getwch();
}

void EditorItem::save()
{
	ofstream fout("StoreWeapon.swp", ios_base::out | ios_base::binary);

	if (fout.is_open())
	{
		unsigned int weaponsCount = mWeapons.size();
		fout.write((char*)&weaponsCount, sizeof(unsigned int));

		for (size_t i = 0; i < weaponsCount; i++)
		{
			mWeapons[i]->Save(fout);
		}

		fout.close();
	}

	fout.open("StoreArmor.sar", ios_base::out | ios_base::binary);

	if (fout.is_open())
	{
		unsigned int armorsCount = mArmors.size();
		fout.write((char*)&armorsCount, sizeof(unsigned int));;

		for (size_t i = 0; i < armorsCount; i++)
		{
			mArmors[i]->Save(fout);
		}

		fout.close();
	}

	cout << endl << "Save complete" << endl;
	_getwch();
}

void EditorItem::load()
{
	for (auto& weapon : mWeapons)
	{
		delete weapon;
	}
	mWeapons.clear();

	for (auto& armor : mArmors)
	{
		delete armor;
	}
	mArmors.clear();

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
			mWeapons.push_back(item);
		}

		fin.close();
	}

	fin.open("StoreArmor.sar", ios_base::in | ios_base::binary);

	if (fin.is_open())
	{
		unsigned int armorsCount = 0;
		fin.read((char*)&armorsCount, sizeof(unsigned int));

		for (size_t i = 0; i < armorsCount; i++)
		{
			Item* item = new ItemArmor(eObjectType::ARMOR);
			item->Initialize();

			item->Load(fin);
			mArmors.push_back(item);
		}

		fin.close();
	}

	cout << endl << "Load complete" << endl;
	_getwch();
}

void EditorItem::inputInt(const char* property, int& data)
{
	while (true)
	{
		cout << property << " : ";
		cin >> data;

		if (cin.fail())
		{
			cout << "Invalid Input" << endl;
			cin.clear();
			cin.ignore(LLONG_MAX, '\n');
			continue;
		}

		cin.ignore(LLONG_MAX, '\n');
		return;
	}
}

void EditorItem::inputFloat(const char* property, float& data)
{
	while (true)
	{
		cout << property << " : ";
		cin >> data;

		if (cin.fail())
		{
			cout << "Invalid Input" << endl;
			cin.clear();
			cin.ignore(LLONG_MAX, '\n');
			continue;
		}

		cin.ignore(LLONG_MAX, '\n');
		return;
	}
}