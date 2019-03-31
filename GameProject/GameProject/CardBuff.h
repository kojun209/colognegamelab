#pragma once

#include "Card.h"
#include "EBuffFlag.h"

struct BuffCardInfo
{
	eBuffFlag BuffType;
	std::string BuffName;
	int BuffCount;
};

class CardBuff :
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

	inline void SetBuffCardInfo(eBuffFlag buffType, int buffCount);

private:
	CardBuff(eObjectType objectType);
	CardBuff(const CardBuff& other);
	virtual ~CardBuff();

private:
	BuffCardInfo mBuffCardInfo;
};

inline void CardBuff::SetBuffCardInfo(eBuffFlag buffType, int buffCount)
{
	mBuffCardInfo.BuffType = buffType;
	mBuffCardInfo.BuffCount = buffCount;

	switch (buffType)
	{
	case eBuffFlag::NONE:
		mBuffCardInfo.BuffName = "None";
		break;
	case eBuffFlag::STRENGTH:
		mBuffCardInfo.BuffName = "Strength";
		break;
	case eBuffFlag::BLOCK:
		mBuffCardInfo.BuffName = "Block";
		break;
	case eBuffFlag::CATALYST:
		mBuffCardInfo.BuffName = "Catalyst";
		break;
	default:
		break;
	}
}
