#pragma once

#include "Object.h"
#include "EBuffFlag.h"
#include "EDebuffFlag.h"

struct CharacterInfo
{
	int Attack;
	int Defense;
	int Hp;
	int HpMax;
	int Level;
	int Exp;
};

class Character :
	public Object
{
	// ...
public:
	virtual void Initialize() override = 0;
	virtual void Render() const override = 0;
	virtual Character* Clone() const override = 0;
	virtual void Save(std::ofstream& fout) override;
	virtual void Load(std::ifstream& fin) override;

	inline void SetCharacterInfo(int attack, int defense, int hp, int level, int exp);
	inline int GetAttack() const;
	inline int GetDefense() const;
	inline void SubtractDamage(int damage);
	inline bool IsDead() const;
	inline CharacterInfo GetCharacterInfo() const;
	inline void SetBuffFlag(eBuffFlag flag, int number);
	inline uint8_t GetBuffFlag(eBuffFlag flag) const;
	inline void SetDebuffFlag(eDebuffFlag flag, int number);
	inline uint8_t GetDebuffFlag(eDebuffFlag flag) const;
	inline void ClearBuffFlag();	// clear flags when a combat ends
	inline void ClearDebuffFlag();
	inline void DecreaseBuffFlag();	// decrease flags at the end of a turn in combat
	inline void DecreaseDebuffFlag();

protected:
	Character(eObjectType objectType);
	Character(const Character& other);
	virtual ~Character() override = 0;

protected:
	CharacterInfo mCharacterInfo;
	int mBuffFlag[static_cast<unsigned int>(eBuffFlag::COUNT)];
	int mDebuffFlag[static_cast<unsigned int>(eDebuffFlag::COUNT)];
};

inline void Character::SetCharacterInfo(int attack, int defense, int hp, int level, int exp)
{
	mCharacterInfo.Attack = attack;
	mCharacterInfo.Defense = defense;
	mCharacterInfo.Hp = hp;
	mCharacterInfo.HpMax = hp;
	mCharacterInfo.Level = level;
	mCharacterInfo.Exp = exp;
}

inline int Character::GetAttack() const
{
	return mCharacterInfo.Attack;
}

inline int Character::GetDefense() const
{
	return mCharacterInfo.Defense;
}

inline void Character::SubtractDamage(int damage)
{
	mCharacterInfo.Hp -= damage;
}

inline bool Character::IsDead() const
{
	return mCharacterInfo.Hp <= 0;
}

inline CharacterInfo Character::GetCharacterInfo() const
{
	return mCharacterInfo;
}

inline void Character::SetBuffFlag(eBuffFlag flag, int number)
{
	mBuffFlag[static_cast<unsigned int>(flag)] += number;
}

inline uint8_t Character::GetBuffFlag(eBuffFlag flag) const
{
	return mBuffFlag[static_cast<unsigned int>(flag)];
}

inline void Character::SetDebuffFlag(eDebuffFlag flag, int number)
{
	mDebuffFlag[static_cast<unsigned int>(flag)] += number;
}

inline uint8_t Character::GetDebuffFlag(eDebuffFlag flag) const
{
	return mDebuffFlag[static_cast<unsigned int>(flag)];
}

inline void Character::ClearBuffFlag()
{
	memset(mBuffFlag, 0, sizeof(int) * static_cast<unsigned int>(eBuffFlag::COUNT));
}

inline void Character::ClearDebuffFlag()
{
	memset(mDebuffFlag, 0, sizeof(int) * static_cast<unsigned int>(eDebuffFlag::COUNT));
}

inline void Character::DecreaseBuffFlag()
{
	for (size_t i = 0; i < static_cast<unsigned int>(eBuffFlag::COUNT); i++)
	{
		if (mBuffFlag[i] > 0)
		{
			mBuffFlag[i] -= 1;
		}
	}
}

inline void Character::DecreaseDebuffFlag()
{
	for (size_t i = 0; i < static_cast<unsigned int>(eDebuffFlag::COUNT); i++)
	{
		if (mDebuffFlag[i] > 0)
		{
			mDebuffFlag[i] -= 1;
		}
	}
}
