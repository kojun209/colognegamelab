#include <iostream>
#include <fstream>

#include "ItemArmor.h"

using namespace std;

void ItemArmor::Initialize()
{
}

void ItemArmor::Render() const
{
	cout << mObjectName << endl;
	cout << "Type : " << mItemInfo.TypeName << "\t\tDefense : " << mDefense << "(+" << GetUpgradedDefense() - GetDefense() << ")" << " (Upgrade Level : " << mUpgradeLevel << ")" << endl;
	cout << "Price to buy: " << mItemInfo.PriceToBuy << "\tPrice to sell : " << mItemInfo.PriceToSell << endl;
	cout << "Description : " << mItemInfo.Description << endl;
	cout << endl;
	cout << "Option : " << mOption.OptionName;

	if (mOption.Option != eArmorOption::AO_NONE)
	{
		cout << " " << mOption.Value << "%" << endl;
		cout << mOption.Description << endl;
	}
	else
	{
		cout << endl;
	}
}

Item* ItemArmor::Clone() const
{
	return new ItemArmor(*this);
}

void ItemArmor::Save(std::ofstream& fout)
{
	Item::Save(fout);

	fout.write((char*)&mDefense, sizeof(int));
	fout.write((char*)&mOption.Option, sizeof(eArmorOption));

	int optionNameSize = mOption.OptionName.size();

	fout.write((char*)&optionNameSize, sizeof(int));
	fout.write(mOption.OptionName.c_str(), optionNameSize);

	fout.write((char*)&mOption.Value, sizeof(float));

	int descriptionSize = mOption.Description.size();

	fout.write((char*)&descriptionSize, sizeof(int));
	fout.write(mOption.Description.c_str(), descriptionSize);
}

void ItemArmor::Load(std::ifstream& fin)
{
	Item::Load(fin);

	fin.read((char*)&mDefense, sizeof(int));
	fin.read((char*)&mOption.Option, sizeof(eArmorOption));

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

ItemArmor::ItemArmor(eObjectType objectType)
	: Item(objectType)
{
}

ItemArmor::ItemArmor(const ItemArmor& other)
	: Item(other)
	, mDefense(other.mDefense)
	, mOption(other.mOption)
{
}

ItemArmor::~ItemArmor()
{
}
