#pragma once

#include <vector>
#include "Singleton.h"

class Item;

class Inventory
{
public:
	DECLARE_SINGLETON(Inventory)
	
	void Initialize();
	void Run();

	inline void AddItem(Item* item);
	inline void SetCapacity(int capacity);
	inline int GetCapacity() const;
	inline bool IsFull() const;

private:
	std::vector<Item*> mItems;
	int mCapacity;
};

inline void Inventory::AddItem(Item* item)
{
	mItems.push_back(item);
}

inline void Inventory::SetCapacity(int capacity)
{
	mCapacity = capacity;
}

inline int Inventory::GetCapacity() const
{
	return mCapacity;
}

inline bool Inventory::IsFull() const
{
	return mCapacity == mItems.size();
}