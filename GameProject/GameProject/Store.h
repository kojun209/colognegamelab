#pragma once

#include <vector>

class Store
{
	friend class StoreManager;

public:
	virtual void Initialize() = 0;
	virtual void Run() = 0;

protected:
	Store();
	virtual ~Store();

	void outputItemList();
	void outputCardList();

protected:
	std::vector<class Item*> mItems;
	std::vector<class Card*> mCards;
};