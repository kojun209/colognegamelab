#pragma once

#include "Card.h"
#include "EDebuffFlag.h"

struct DebuffCardInfo
{
	eDebuffFlag DebuffType;
	std::string DebuffName;
	int DebuffCount;
};

class CardDebuff :
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

	inline void SetDebuffCardInfo(eDebuffFlag debuffType, int debuffCount);

private:
	CardDebuff(eObjectType objectType);
	CardDebuff(const CardDebuff& other);
	virtual ~CardDebuff();

private:
	DebuffCardInfo mDebuffCardInfo;
};

inline void CardDebuff::SetDebuffCardInfo(eDebuffFlag debuffType, int debuffCount)
{
	mDebuffCardInfo.DebuffType = debuffType;
	mDebuffCardInfo.DebuffCount = debuffCount;

	switch (debuffType)
	{
	case eDebuffFlag::NONE:
		mDebuffCardInfo.DebuffName = "None";
		break;
	case eDebuffFlag::VULNERABLE:
		mDebuffCardInfo.DebuffName = "Vulnerable";
		break;
	case eDebuffFlag::WEAK:
		mDebuffCardInfo.DebuffName = "Weak";
		break;
	case eDebuffFlag::DEADLY_POISON:
		mDebuffCardInfo.DebuffName = "Deadly Poison";
		break;
	case eDebuffFlag::TIME_ABSORPTION:
		mDebuffCardInfo.DebuffName = "Time absorption";
		break;
	default:
		break;
	}
}
