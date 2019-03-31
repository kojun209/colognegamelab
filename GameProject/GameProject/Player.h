#pragma once

#include "Character.h"
#include "EClassType.h"
#include "LevelUpTable.h"
#include "FixedVector.h"
#include "ItemWeapon.h"
#include "ItemArmor.h"
#include "EEquippedItemType.h"
#include "ECardDeckInfo.h"

enum { INITIAL_ENERGY = 3 };

class Item;
class Card;

class Player final :
	public Character
{
	friend class ObjectManager;
	friend class Inventory;

public:
	virtual void Initialize() override;
	virtual void Render() const override;
	virtual Player* Clone() const override;
	Item* EquipItemOrNull(Item* item);

	inline void AddGold(int gold);
	inline bool AddExp(int exp);	// return true if level up
	inline void LevelUp();
	inline void AddLevelUpStatus(const LevelUpInfo& info);
	inline void AddCard(Card* card);
	inline eClassType GetClassType() const;
	inline int GetGold() const;
	inline FixedVector<class Card*, 20> GetCards() const;
	inline int GetEnergy() const;
	inline void SetEnergy(int energy);
	inline int GetItemAttack() const;
	inline void AddEnergy(int energy);
	inline void SubtractEnergy(int energy);
	inline ItemWeapon* GetWeapon() const;
	inline ItemArmor* GetArmor() const;

private:
	Player(eObjectType objectType);
	virtual ~Player() override;

private:
	eClassType mClassType;
	std::string mClassName;
	int mGold;
	Item* mItems[eEquippedItemType::EQ_COUNT];
	FixedVector<class Card*, eCardDeckInfo::CARD_DECK_MAX> mCards;
	int mEnergy;
};

inline void Player::AddGold(int gold)
{
	mGold += gold;
}

inline bool Player::AddExp(int exp)
{
	mCharacterInfo.Exp += exp;

	return LEVEL_UP_TABLE[mCharacterInfo.Level - 1] <= mCharacterInfo.Exp;
}

inline void Player::LevelUp()
{
	mCharacterInfo.Exp -= LEVEL_UP_TABLE[mCharacterInfo.Level - 1];
	mCharacterInfo.Level++;
}

inline void Player::AddLevelUpStatus(const LevelUpInfo& info)
{
	mCharacterInfo.Attack += info.Attack;
	mCharacterInfo.Defense += info.Defense;
	mCharacterInfo.HpMax += info.Hp;
	mCharacterInfo.Hp = mCharacterInfo.HpMax;
}

inline void Player::AddCard(Card* card)
{
	mCards.Add(card);
}

inline eClassType Player::GetClassType() const
{
	return mClassType;
}

inline int Player::GetGold() const
{
	return mGold;
}

inline FixedVector<class Card*, eCardDeckInfo::CARD_DECK_MAX> Player::GetCards() const
{
	return mCards;
}

inline int Player::GetEnergy() const
{
	return mEnergy;
}

inline void Player::SetEnergy(int energy)
{
	mEnergy = energy;
}

inline int Player::GetItemAttack() const
{
	if (mItems[eEquippedItemType::EQ_WEAPON] == nullptr)
	{
		return NULL;
	}

	return static_cast<ItemWeapon*>(mItems[eEquippedItemType::EQ_WEAPON])->GetUpgradedAttack();
}

inline void Player::AddEnergy(int energy)
{
	mEnergy += energy;
}

inline void Player::SubtractEnergy(int energy)
{
	mEnergy -= energy;
}

inline ItemWeapon* Player::GetWeapon() const
{
	return static_cast<ItemWeapon*>(mItems[eEquippedItemType::EQ_WEAPON]);
}

inline ItemArmor* Player::GetArmor() const
{
	return static_cast<ItemArmor*>(mItems[eEquippedItemType::EQ_ARMOR]);
}
