#pragma once

#include "Card.h"

struct SkillCardInfo
{
	int mHPValue;
	int mEnergyValue;
};

class CardSkill :
	public Card
{
	friend class EditorCard;
	friend class StoreCard;
	friend class ObjectManager;

public:
	virtual void Initialize() override;
	virtual Card* Clone() const override;
	virtual void Save(std::ofstream& fout) override;
	virtual void Load(std::ifstream& fin) override;
	virtual eCombatResult ActivateCard(Player* player, Monster* monster) const override;

	inline void SetSkillCardInfo(int hp, int energy);

private:
	CardSkill(eObjectType objectType);
	CardSkill(const CardSkill& other);
	virtual ~CardSkill();

private:
	SkillCardInfo mSkillCardInfo;
};

inline void CardSkill::SetSkillCardInfo(int hp, int energy)
{
	mSkillCardInfo.mHPValue = hp;
	mSkillCardInfo.mEnergyValue = energy;
}