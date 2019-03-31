#include <iostream>
#include <fstream>

#include "Card.h"
#include "Player.h"

using namespace std;

Card::Card(eObjectType objectType)
	: Object(objectType)
{
}

Card::Card(const Card& other)
	: Object(other)
	, mCardType(other.mCardType)
	, mCardTypeName(other.mCardTypeName)
	, mEnergyCost(other.mEnergyCost)
	, mDescription(other.mDescription)
	, mPriceToBuy(other.mPriceToBuy)
	, mPriceToSell(other.mPriceToSell)
{
}

Card::~Card()
{
}

void Card::SetCardInfo(eCardType cardType, int energyCost, const char* description, int priceToBuy, int priceToSell)
{
	mCardType = cardType;

	switch (cardType)
	{
	case CT_ATTACK:
		mCardTypeName = "Attack";
		break;
	case CT_SKILL:
		mCardTypeName = "Skill";
		break;
	case CT_BUFF:
		mCardTypeName = "Buff";
		break;
	case CT_DEBUFF:
		mCardTypeName = "Debuff";
		break;
	default:
		break;
	}

	mEnergyCost = energyCost;
	mDescription = description;
	mPriceToBuy = priceToBuy;
	mPriceToSell = priceToSell;
}

bool Card::CanAfford(Player* player) const
{
	if (player->GetEnergy() < mEnergyCost)
	{
		cout << "Not enough energy" << endl;
		_getwch();
		return false;
	}

	return true;
}

void Card::Render() const
{
	cout << mObjectName << endl;
	cout << "Type : " << mCardTypeName << "\tEnergy cost : " << mEnergyCost << endl;
	cout << "Description : " << mDescription << endl;
}

void Card::OutputPrice() const
{
	cout << "Price to buy : " << mPriceToBuy << "\tPrice to sell : " << mPriceToSell << endl;
}

void Card::Save(std::ofstream& fout)
{
	Object::Save(fout);

	fout.write((char*)&mCardType, sizeof(mCardType));

	unsigned int typeNameSize = mCardTypeName.size();

	fout.write((char*)&typeNameSize, sizeof(unsigned int));
	fout.write(mCardTypeName.c_str(), typeNameSize);

	fout.write((char*)&mEnergyCost, sizeof(int));

	unsigned int descriptionSize = mDescription.size();

	fout.write((char*)&descriptionSize, sizeof(unsigned int));
	fout.write(mDescription.c_str(), descriptionSize);

	fout.write((char*)&mPriceToBuy, sizeof(int));
	fout.write((char*)&mPriceToSell, sizeof(int));
}

void Card::Load(std::ifstream& fin)
{
	Object::Load(fin);

	fin.read((char*)&mCardType, sizeof(mCardType));

	unsigned int typeNameSize = 0;
	fin.read((char*)&typeNameSize, sizeof(unsigned int));

	constexpr int NAME_SIZE = 16;
	char typeName[NAME_SIZE];

	fin.read(typeName, typeNameSize);
	typeName[typeNameSize] = '\0';
	mCardTypeName = typeName;

	fin.read((char*)&mEnergyCost, sizeof(int));

	unsigned int descriptionSize = 0;
	fin.read((char*)&descriptionSize, sizeof(unsigned int));

	constexpr int DESCRIPTION_SIZE = 128;
	char description[DESCRIPTION_SIZE];

	fin.read(description, descriptionSize);
	description[descriptionSize] = '\0';
	mDescription = description;

	fin.read((char*)&mPriceToBuy, sizeof(int));
	fin.read((char*)&mPriceToSell, sizeof(int));
}