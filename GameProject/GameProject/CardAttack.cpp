#include <iostream>
#include <fstream>

#include "CardAttack.h"
#include "Monster.h"
#include "Player.h"

using namespace std;

CardAttack::CardAttack(eObjectType objectType)
	: Card(objectType)
{
	mAttackCardInfo = {};
}

CardAttack::CardAttack(const CardAttack& other)
	: Card(other)
	, mAttackCardInfo(other.mAttackCardInfo)
	, mDebuffName(other.mDebuffName)
{
}

CardAttack::~CardAttack()
{
}

void CardAttack::Initialize()
{
}

Card* CardAttack::Clone() const
{
	return new CardAttack(*this);
}

void CardAttack::Save(std::ofstream& fout)
{
	Card::Save(fout);

	fout.write((char*)&mAttackCardInfo, sizeof(AttackCardInfo));

	int debuffNameSize = mDebuffName.size();

	fout.write((char*)&debuffNameSize, sizeof(int));
	fout.write(mDebuffName.c_str(), debuffNameSize);
}

void CardAttack::Load(std::ifstream& fin)
{
	Card::Load(fin);

	fin.read((char*)&mAttackCardInfo, sizeof(AttackCardInfo));

	int debuffNameSize = 0;
	fin.read((char*)&debuffNameSize, sizeof(int));

	constexpr int DEBUFF_NAME_SIZE = 16;
	char debuffName[DEBUFF_NAME_SIZE];

	fin.read(debuffName, debuffNameSize);
	debuffName[debuffNameSize] = '\0';
	mDebuffName = debuffName;
}

eCombatResult CardAttack::ActivateCard(Player* player, Monster* monster) const
{
	float attack = 0;
	int damage = 0;

	attack = player->GetAttack() * mAttackCardInfo.mPlayerAttackValue + player->GetItemAttack() * mAttackCardInfo.mWeaponAttackValue;

	if (player->GetBuffFlag(eBuffFlag::STRENGTH))
	{
		attack = attack * 1.5f;
	}

	if (player->GetDebuffFlag(eDebuffFlag::WEAK))
	{
		attack = attack * 0.75f;
	}

	int monsterDefense = monster->GetDefense();

	if (player->GetWeapon() && 
		player->GetWeapon()->GetWeaponOption().Option == eWeaponOption::IGNORE_DEFENSE)
	{
		float value = player->GetWeapon()->GetWeaponOption().Value;
		monsterDefense = static_cast<int>(monsterDefense * (1 - value / 100.f));
		cout << "Ignores " << value << "% of monster's defense" << endl << endl;
	}

	damage = (static_cast<int>(attack) - monsterDefense) * mAttackCardInfo.mAttackCount;

	if (monster->GetDebuffFlag(eDebuffFlag::VULNERABLE))
	{
		damage = static_cast<int>(damage * 1.5f);
	}

	damage = damage < 1 ? 1 : damage;

	monster->SubtractDamage(damage);

	cout << player->GetName() << " attacks " << monster->GetName();
	if (mAttackCardInfo.mAttackCount <= 1)
	{
		cout << endl;
	}
	else
	{
		cout << " " << mAttackCardInfo.mAttackCount << " times!" << endl;
	}
	_getwch();
	cout << player->GetName() << " hits for " << damage << " damage to " << monster->GetName() << "." << endl;

	if (monster->IsDead())
	{
		return eCombatResult::MONSTER_DIE;
	}

	if (mAttackCardInfo.mDebuff != eDebuffFlag::NONE)
	{
		monster->SetDebuffFlag(mAttackCardInfo.mDebuff, mAttackCardInfo.mDebuffCount);
		_getwch();
		cout << endl;
		cout << monster->GetName() << " got " << mDebuffName << endl;
	}

	if (player->IsDead())
	{
		return eCombatResult::PLAYER_DIE;
	}

	return eCombatResult::NONE;
}


