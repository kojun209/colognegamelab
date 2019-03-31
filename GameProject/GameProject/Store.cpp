#include <iostream>

#include "Store.h"
#include "Item.h"
#include "Card.h"

using namespace std;

Store::Store()
{
}

Store::~Store()
{
	for (auto& item : mItems)
	{
		delete item;
	}
}

void Store::outputItemList()
{
	for (size_t i = 0; i < mItems.size(); i++)
	{
		cout << i + 1 << ". ";
		mItems[i]->Render();
		cout << endl;
	}
}

void Store::outputCardList()
{
	for (size_t i = 0; i < mCards.size(); i++)
	{
		cout << i + 1 << ". ";
		mCards[i]->Render();
		mCards[i]->OutputPrice();
		cout << endl;
	}
}