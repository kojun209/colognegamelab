#include <fstream>

#include "Item.h"

Item::Item(eObjectType objectType)
	: Object(objectType)
	, mUpgradeLevel(0)
{
}

Item::Item(const Item& other)
	: Object(other)
	, mItemInfo(other.mItemInfo)
	, mUpgradeLevel(other.mUpgradeLevel)
{
}

Item::~Item()
{
}

void Item::Save(std::ofstream& fout)
{
	Object::Save(fout);

	fout.write((char*)&mItemInfo.Type, sizeof(eItemType));

	unsigned int typeNameSize = mItemInfo.TypeName.size();

	fout.write((char*)&typeNameSize, sizeof(unsigned int));
	fout.write(mItemInfo.TypeName.c_str(), typeNameSize);

	fout.write((char*)&mItemInfo.PriceToBuy, sizeof(int));
	fout.write((char*)&mItemInfo.PriceToSell, sizeof(int));

	unsigned int descriptionSize = mItemInfo.Description.size();

	fout.write((char*)&descriptionSize, sizeof(unsigned int));
	fout.write(mItemInfo.Description.c_str(), descriptionSize);

	fout.write((char*)&mUpgradeLevel, sizeof(int));
}

void Item::Load(std::ifstream& fin)
{
	Object::Load(fin);

	fin.read((char*)&mItemInfo.Type, sizeof(eItemType));

	unsigned int typeNameSize = 0;
	fin.read((char*)&typeNameSize, sizeof(unsigned int));

	constexpr int NAME_SIZE = 16;
	char typeName[NAME_SIZE];

	fin.read(typeName, typeNameSize);
	typeName[typeNameSize] = '\0';
	mItemInfo.TypeName = typeName;

	fin.read((char*)&mItemInfo.PriceToBuy, sizeof(int));
	fin.read((char*)&mItemInfo.PriceToSell, sizeof(int));

	unsigned int descriptionSize = 0;
	fin.read((char*)&descriptionSize, sizeof(unsigned int));

	constexpr int DESCRIPTION_SIZE = 128;
	char description[DESCRIPTION_SIZE];

	fin.read(description, descriptionSize);
	description[descriptionSize] = '\0';
	mItemInfo.Description = description;

	fin.read((char*)&mUpgradeLevel, sizeof(int));
}

void Item::SetItemInfo(eItemType type, int priceToBuy, int priceToSell, const char* description)
{
	mItemInfo.Type = type;

	switch (type)
	{
	case eItemType::WEAPON:
		mItemInfo.TypeName = "Weapon";
		break;
	case eItemType::ARMOR:
		mItemInfo.TypeName = "Armor";
		break;
	default:
		break;
	}

	mItemInfo.PriceToBuy = priceToBuy;
	mItemInfo.PriceToSell = priceToSell;
	mItemInfo.Description = description;
}