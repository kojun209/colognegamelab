#pragma once

#include "Card.h"
#include "EDebuffFlag.h"

struct AttackCardInfo
{
	float mPlayerAttackValue;
	float mWeaponAttackValue;
	int mAttackCount;
	eDebuffFlag mDebuff;
	int mDebuffCount;
};

class CardAttack :
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

	inline void SetAttackCardInfo(float playerAttack, float weaponAttack, int attackCount, eDebuffFlag debuff, int debuffCount);

private:
	CardAttack(eObjectType objectType);
	CardAttack(const CardAttack& other);
	virtual ~CardAttack();

private:
	AttackCardInfo mAttackCardInfo;
	std::string mDebuffName;
};

inline void CardAttack::SetAttackCardInfo(float playerAttack, float weaponAttack, int attackCount, eDebuffFlag debuff, int debuffCount)
{
	mAttackCardInfo.mPlayerAttackValue = playerAttack;
	mAttackCardInfo.mWeaponAttackValue = weaponAttack;
	mAttackCardInfo.mAttackCount = attackCount;
	mAttackCardInfo.mDebuff = debuff;
	mAttackCardInfo.mDebuffCount = debuffCount;

	switch (debuff)
	{
	case eDebuffFlag::NONE:
		mDebuffName = "None";
		break;
	case eDebuffFlag::VULNERABLE:
		mDebuffName = "Vulnerable";
		break;
	case eDebuffFlag::WEAK:
		mDebuffName = "Weak";
		break;
	case eDebuffFlag::DEADLY_POISON:
		mDebuffName = "Deadly Poison";
		break;
	case eDebuffFlag::TIME_ABSORPTION:
		mDebuffName = "Time absorption";
		break;
	default:
		break;
	}
}