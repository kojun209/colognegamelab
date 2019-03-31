#pragma once

#include <queue>

#include "EMonsterClass.h"
#include "FixedVector.h"
#include "ECombatResult.h"
#include "ECardDeckInfo.h"
#include "EFloorNumber.h"
#include "EFloorEnd.h"

using namespace std;

class Player;
class Monster;
class Card;

class Floor
{
	friend class FloorManager;

public:
	virtual void Initialize();
	virtual void Run();
	
	inline static int GetKilledMonstersCount();	// return mKilledMonstersCount
	static eMonsterClass OutputMonsterClassMenu();	// 1. Normal	2. Elite	3. Back

protected:
	Floor();
	virtual ~Floor();
	eCombatResult handleCombat(Player* player, Monster* monster);
	void shuffleCards(FixedVector<Card*, eCardDeckInfo::CARD_DECK_MAX>& cards);
	Card* drawCard();	// draw 1 card from Draw Pile. If Draw Pile is empty, get cards from Discard Pile

protected:
	static int mKilledMonstersCount;
	eFloorNumber mFloorNumber;
	FixedVector<Card*, eCardDeckInfo::CARD_DECK_MAX> mDrawPile;
	FixedVector<Card*, eCardDeckInfo::CARD_DECK_MAX> mDiscardPile;
	FixedVector<Card*, eCardDeckInfo::HAND_OF_CARDS_MAX> mHandOfCards;	// cards player can play in each turn
};

inline int Floor::GetKilledMonstersCount()
{
	return mKilledMonstersCount;
}