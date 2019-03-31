#pragma once

#include "Character.h"
#include "EFloorNumber.h"
#include "EMonsterClass.h"
#include "EBuffType.h"
#include "EBuffFlag.h"
#include "EDebuffFlag.h"

struct MonsterBuffInfo
{
	eBuffFlag BuffType;
	std::string BuffName;
	int BuffCount;
};

struct MonsterDebuffInfo
{
	eDebuffFlag DebuffType;
	std::string DebuffName;
	int DebuffCount;
};

class Player;

class Monster final :
	public Character
{
	friend class ObjectManager;
	friend class EditorMonster;

public:
	virtual ~Monster() override;
	virtual void Initialize() override;
	virtual void Render() const override;
	virtual Monster* Clone() const override;
	virtual void Save(std::ofstream& fout) override;
	virtual void Load(std::ifstream& fin) override;
	void ActivateBuff(Player* player, Monster* monster);
	void ActivateDebuff(Player* player, Monster* monster);

	inline void SetDropGold(int min, int max);
	inline int GetDropGold() const;
	inline void SetFloorNumber(eFloorNumber floorNumber);
	inline eFloorNumber GetFloorNumber() const;
	inline void SetMonsterClass(eMonsterClass monsterClass);
	inline eMonsterClass GetMonsterClass() const;
	inline void SetBuffInfo(eBuffFlag buffType, int buffCount);
	inline void SetDebuffInfo(eDebuffFlag debuffType, int debuffCount);

private:
	Monster(eObjectType objectType);
	Monster(const Monster& other);

private:
	int mGoldMin;
	int mGoldMax;
	eFloorNumber mFloorNumber;
	eMonsterClass mMonsterClass;
	MonsterBuffInfo mBuffInfo;
	MonsterDebuffInfo mDebuffInfo;
};

inline void Monster::SetDropGold(int min, int max)
{
	mGoldMin = min;
	mGoldMax = max;
}

inline int Monster::GetDropGold() const
{
	return rand() % (mGoldMax - mGoldMin + 1) + mGoldMin;
}

inline void Monster::SetFloorNumber(eFloorNumber floorNumber)
{
	mFloorNumber = floorNumber;
}

inline eFloorNumber Monster::GetFloorNumber() const
{
	return mFloorNumber;
}

inline void Monster::SetMonsterClass(eMonsterClass monsterClass)
{
	mMonsterClass = monsterClass;
}

inline eMonsterClass Monster::GetMonsterClass() const
{
	return mMonsterClass;
}

inline void Monster::SetBuffInfo(eBuffFlag buffType, int buffCount)
{
	mBuffInfo.BuffType= buffType;
	mBuffInfo.BuffCount = buffCount;

	switch (buffType)
	{
	case eBuffFlag::NONE:
		mBuffInfo.BuffName = "None";
		break;
	case eBuffFlag::STRENGTH:
		mBuffInfo.BuffName = "Strength";
		break;
	case eBuffFlag::BLOCK:
		mBuffInfo.BuffName = "Block";
		break;
	case eBuffFlag::CATALYST:
		mBuffInfo.BuffName = "Catalyst";
		break;
	default:
		break;
	}
}

inline void Monster::SetDebuffInfo(eDebuffFlag debuffType, int debuffCount)
{
	mDebuffInfo.DebuffType = debuffType;
	mDebuffInfo.DebuffCount = debuffCount;

	switch (debuffType)
	{
	case eDebuffFlag::NONE:
		mDebuffInfo.DebuffName = "None";
		break;
	case eDebuffFlag::VULNERABLE:
		mDebuffInfo.DebuffName = "Vulnerable";
		break;
	case eDebuffFlag::WEAK:
		mDebuffInfo.DebuffName = "Weak";
		break;
	case eDebuffFlag::DEADLY_POISON:
		mDebuffInfo.DebuffName = "Deadly Poison";
		break;
	case eDebuffFlag::TIME_ABSORPTION:
		mDebuffInfo.DebuffName = "Time absorption";
		break;
	default:
		break;
	}
}
