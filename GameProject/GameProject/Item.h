#pragma once

#include "Object.h"
#include "EItemType.h"

struct ItemInfo
{
	eItemType Type;
	std::string TypeName;
	int PriceToBuy;
	int PriceToSell;
	std::string Description;
};

class Item :
	public Object
{
	friend class Store;
	friend class EditorItem;
	friend class Inventory;
	friend class Player;

public:
	virtual void Initialize() override = 0;
	virtual void Render() const override = 0;
	virtual Item* Clone() const override = 0;
	virtual void Save(std::ofstream& fout) override;
	virtual void Load(std::ifstream& fin) override;

	void SetItemInfo(eItemType type, int priceToBuy, int priceToSell, const char* description);
	inline ItemInfo GetItemInfo() const;

protected:
	Item(eObjectType objectType);
	Item(const Item& other);
	virtual ~Item() override = 0;

protected:
	ItemInfo mItemInfo;
	int mUpgradeLevel;
};

inline ItemInfo Item::GetItemInfo() const
{
	return mItemInfo;
}
