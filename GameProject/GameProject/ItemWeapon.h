#pragma once

#include "Item.h"
#include "EWeaponOption.h"

class ItemWeapon final :
	public Item
{
	friend class StoreWeapon;
	friend class EditorItem;

public:
	virtual void Initialize() override;
	virtual void Render() const override;
	virtual Item* Clone() const override;
	virtual void Save(std::ofstream& fout) override;
	virtual void Load(std::ifstream& fin) override;

	inline void SetAttack(int attack);
	inline int GetAttack() const;
	inline int GetUpgradedAttack() const;
	inline void SetWeaponOption(eWeaponOption option, float value, const char* description);
	inline WeaponOption GetWeaponOption() const;

private:
	ItemWeapon(eObjectType objectType);
	ItemWeapon(const ItemWeapon& other);
	virtual ~ItemWeapon();

private:
	int mAttack;
	WeaponOption mOption;
};

inline void ItemWeapon::SetAttack(int attack)
{
	mAttack = attack;
}

inline int ItemWeapon::GetAttack() const
{
	return mAttack;
}

inline int ItemWeapon::GetUpgradedAttack() const
{
	float attack = static_cast<float>(mAttack);

	for (int i = 0; i < mUpgradeLevel; i++)
	{
		attack *= (float)(1 + (i + 1) * 0.1);
	}

	return static_cast<int>(attack);
}

inline void ItemWeapon::SetWeaponOption(eWeaponOption option, float value, const char* description)
{
	mOption.Option = option;

	switch (option)
	{
	case WO_NONE:
		mOption.OptionName = "None";
		break;
	case IGNORE_DEFENSE:
		mOption.OptionName = "Ignore defense";
		break;
	default:
		break;
	}

	mOption.Value = value;
	mOption.Description = description;
}

inline WeaponOption ItemWeapon::GetWeaponOption() const
{
	return mOption;
}
