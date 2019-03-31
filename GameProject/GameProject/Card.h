#pragma once

#include "Object.h"
#include "ECardType.h"
#include "ECombatResult.h"

class Player;
class Monster;

class Card : public Object
{
	friend class Player;
	friend class EditorCard;
	friend class StoreCard;
	friend class Floor;

public:
	virtual void Initialize() = 0;
	virtual Card* Clone() const = 0;
	virtual void Render() const;
	virtual void OutputPrice() const;
	virtual void Save(std::ofstream& fout) override;
	virtual void Load(std::ifstream& fin) override;
	virtual eCombatResult ActivateCard(Player* player, Monster* monster) const = 0;

	void SetCardInfo(eCardType cardType, int energyCost, const char* description, int priceToBuy, int priceToSell);
	bool CanAfford(Player* player) const;
	inline int GetCost() const;

protected:
	Card(eObjectType objectType);
	Card(const Card& other);
	virtual ~Card();

private:
	eCardType mCardType;
	std::string mCardTypeName;
	int mEnergyCost;
	std::string mDescription;
	int mPriceToBuy;
	int mPriceToSell;
};

inline int Card::GetCost() const
{
	return mEnergyCost;
}