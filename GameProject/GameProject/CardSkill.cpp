#include <iostream>
#include <fstream>

#include "CardSkill.h"
#include "Player.h"

using namespace std;

CardSkill::CardSkill(eObjectType objectType)
	: Card(objectType)
{
	mSkillCardInfo = {};
}

CardSkill::CardSkill(const CardSkill& other)
	: Card(other)
	, mSkillCardInfo(other.mSkillCardInfo)
{
}

CardSkill::~CardSkill()
{
}

void CardSkill::Initialize()
{
}

Card* CardSkill::Clone() const
{
	return new CardSkill(*this);
}

void CardSkill::Save(std::ofstream& fout)
{
	Card::Save(fout);

	fout.write((char*)&mSkillCardInfo, sizeof(SkillCardInfo));
}

void CardSkill::Load(std::ifstream& fin)
{
	Card::Load(fin);

	fin.read((char*)&mSkillCardInfo, sizeof(SkillCardInfo));
}

eCombatResult CardSkill::ActivateCard(Player* player, Monster* monster) const
{
	int damage = static_cast<int>(player->GetCharacterInfo().Hp * mSkillCardInfo.mHPValue * 0.01f);
	player->SubtractDamage(damage);
	player->AddEnergy(mSkillCardInfo.mEnergyValue);

	cout << "Lost " << mSkillCardInfo.mHPValue << " %of HP." <<  " Got " << mSkillCardInfo.mEnergyValue << " energy.";
	
	if (player->IsDead())
	{
		return eCombatResult::PLAYER_DIE;
	}

	return eCombatResult::NONE;
}
