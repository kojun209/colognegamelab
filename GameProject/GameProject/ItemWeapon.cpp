#include <iostream>
#include <fstream>

#include "ItemWeapon.h"

using namespace std;

void ItemWeapon::Initialize()
{
}

void ItemWeapon::Render() const
{
	cout << mObjectName << endl;
	cout << "Type : " << mItemInfo.TypeName << "\t\tAttack : " << mAttack << "(+" << GetUpgradedAttack() - GetAttack() << ")" << " (Upgrade Level : " << mUpgradeLevel << ")" << endl;
	cout << "Price to buy: " << mItemInfo.PriceToBuy << "\tPrice to sell : " << mItemInfo.PriceToSell << endl;
	cout << "Description : " << mItemInfo.Description << endl;
	cout << endl;
	cout << "Option : " << mOption.OptionName;

	if (mOption.Option != eWeaponOption::WO_NONE)
	{
		cout << " " << mOption.Value << "%" << endl;
		cout << mOption.Description << endl;
	}
	else
	{
		cout << endl;
	}
}

Item* ItemWeapon::Clone() const
{
	return new ItemWeapon(*this);
}

void ItemWeapon::Save(std::ofstream& fout)
{
	Item::Save(fout);

	fout.write((char*)&mAttack, sizeof(int));
	fout.write((char*)&mOption.Option, sizeof(eWeaponOption));

	int optionNameSize = mOption.OptionName.size();

	fout.write((char*)&optionNameSize, sizeof(int));
	fout.write(mOption.OptionName.c_str(), optionNameSize);

	fout.write((char*)&mOption.Value, sizeof(float));

	int descriptionSize = mOption.Description.size();

	fout.write((char*)&descriptionSize, sizeof(int));
	fout.write(mOption.Description.c_str(), descriptionSize);
}

void ItemWeapon::Load(std::ifstream& fin)
{
	Item::Load(fin);

	fin.read((char*)&mAttack, sizeof(int));
	fin.read((char*)&mOption.Option, sizeof(eWeaponOption));

	int optionNameSize = 0;
	fin.read((char*)&optionNameSize, sizeof(int));

	constexpr int OPTION_NAME_SIZE = 32;
	char optionName[OPTION_NAME_SIZE];

	fin.read(optionName, optionNameSize);
	optionName[optionNameSize] = '\0';
	mOption.OptionName = optionName;

	fin.read((char*)&mOption.Value, sizeof(float));

	int descriptionSize = 0;
	fin.read((char*)&descriptionSize, sizeof(int));

	constexpr int DESCRIPTION_SIZE = 128;
	char description[DESCRIPTION_SIZE];

	fin.read(description, descriptionSize);
	description[descriptionSize] = '\0';
	mOption.Description = description;
}

ItemWeapon::ItemWeapon(eObjectType objectType)
	: Item(objectType)
{
}

ItemWeapon::ItemWeapon(const ItemWeapon& other)
	: Item(other)
	, mAttack(other.mAttack)
	, mOption(other.mOption)
{
}

ItemWeapon::~ItemWeapon()
{
}
