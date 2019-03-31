#pragma once

#include "Item.h"
#include "EArmorOption.h"

class ItemArmor final :
	public Item
{
	friend class StoreArmor;
	friend class EditorItem;

public:
	virtual void Initialize() override;
	virtual void Render() const override;
	virtual Item* Clone() const override;
	virtual void Save(std::ofstream& fout) override;
	virtual void Load(std::ifstream& fin) override;

	inline void SetDefense(int defense);
	inline int GetDefense() const;
	inline int GetUpgradedDefense() const;
	inline void SetArmorOption(eArmorOption option, float value, const char* description);
	inline ArmorOption GetArmorOption() const;

private:
	ItemArmor(eObjectType objectType);
	ItemArmor(const ItemArmor& other);
	virtual ~ItemArmor();

private:
	int mDefense;
	ArmorOption mOption;
};

inline void ItemArmor::SetDefense(int defense)
{
	mDefense = defense;
}

inline int ItemArmor::GetDefense() const
{
	return mDefense;
}

// An upgrade increases the item ability like a compound interest
inline int ItemArmor::GetUpgradedDefense() const	
{													
	float defense = static_cast<float>(mDefense);	

	for (int i = 0; i < mUpgradeLevel; i++)
	{
		defense *= (float)(1 + (i + 1) * 0.1);
	}

	return static_cast<int>(defense);
}

inline void ItemArmor::SetArmorOption(eArmorOption option, float value, const char* description)
{
	mOption.Option = option;

	switch (option)
	{
	case AO_NONE:
		mOption.OptionName = "None";
		break;
	case THORN:
		mOption.OptionName = "Thorn";
		break;
	default:
		break;
	}

	mOption.Value = value;
	mOption.Description = description;
}

inline ArmorOption ItemArmor::GetArmorOption() const
{
	return mOption;
}