#include <iostream>

#include "Player.h"
#include "Card.h"
#include "ObjectManager.h"

using namespace std;

void Player::Initialize()
{
	system("cls");
	cout << "Enter your name : ";

	constexpr int NAME_SIZE = 32;
	char name[NAME_SIZE] = {};

	cin.getline(name, NAME_SIZE);
	SetName(name);

	int input = 0;
	while (input < eClassType::KNIGHT || input > eClassType::KNIGHT)
	{
		system("cls");
		cout << "1. Knight" << endl;
		cout << "Select your class : ";

		input = _getwche() - 48;
	}

	mClassType = static_cast<eClassType>(input);
	mGold = 1000000;

	switch (mClassType)
	{
	case KNIGHT:
		mClassName = "Knight";
		SetCharacterInfo(10, 15, 500, 1, 0);
		break;
	default:
		break;
	}

	constexpr int INITIAL_CARDS_COUNT = 5;
	for (size_t i = 0; i < INITIAL_CARDS_COUNT; i++)
	{
		mCards.Add(static_cast<Card*>(ObjectManager::GetInstance()->CloneObject("Strike")));
	}
}

void Player::Render() const
{
	cout << "Name : " << mObjectName << "\t" << mClassName << endl;
	cout << "Level : " << mCharacterInfo.Level << "\tExp : " << mCharacterInfo.Exp << endl;
	cout << "Attack : ";
	
	ItemWeapon* weapon = static_cast<ItemWeapon*>(mItems[eEquippedItemType::EQ_WEAPON]);
	if (weapon)
	{
		cout << mCharacterInfo.Attack << "+(" << weapon->GetUpgradedAttack() << ")";
	}
	else
	{
		cout << mCharacterInfo.Attack;
	}

	cout << "\tDefense : ";
	
	ItemArmor* armor = static_cast<ItemArmor*>(mItems[eEquippedItemType::EQ_ARMOR]);
	if (armor)
	{
		cout << mCharacterInfo.Defense << "+(" << armor->GetUpgradedDefense() << ")" << endl;
	}
	else
	{
		cout << mCharacterInfo.Defense << endl;
	}

	cout << "HP : " << mCharacterInfo.Hp << " / " << mCharacterInfo.HpMax << endl;
	cout << "Weapon : ";
	if (weapon)
	{
		cout << weapon->GetName();
	}
	else
	{
		cout << "None";
	}

	cout << "\tArmor :";
	if (armor)
	{
		cout << armor->GetName() << endl;
	}
	else
	{
		cout << "None" << endl;
	}
}

Player* Player::Clone() const
{
	return new Player(*this);
}

Item* Player::EquipItemOrNull(Item* item)
{
	eEquippedItemType equippedItemType;

	switch (item->GetItemInfo().Type)
	{
	case eItemType::WEAPON:
		equippedItemType = eEquippedItemType::EQ_WEAPON;
		break;
	case eItemType::ARMOR:
		equippedItemType = eEquippedItemType::EQ_ARMOR;
		break;
	default:
		break;
	}

	if (mItems[equippedItemType])
	{
		Item* equippedItem = mItems[equippedItemType];
		mItems[equippedItemType] = item;

		return equippedItem;
	}

	mItems[equippedItemType] = item;

	return NULL;
}

Player::Player(eObjectType objectType)
	: Character(objectType)
	, mGold(0)
	, mEnergy(INITIAL_ENERGY)
{
	memset(mItems, 0, sizeof(Item*) * EQ_COUNT);
}

Player::~Player()
{
	for (auto& item : mItems)
	{
		delete item;
	}

	for (size_t i = 0; i < mCards.GetSize(); i++)
	{
		delete mCards[i];
	}
}