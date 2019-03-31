#pragma once

#include <vector>
#include "Singleton.h"

class EditorItem
{
public:
	DECLARE_SINGLETON(EditorItem)

	void Initialize();
	void Run();

private:
	int outputMenu();
	void add();
	void remove();
	void list();
	void save();
	void load();
	void inputInt(const char* property, int& data);
	void inputFloat(const char* property, float& data);

private:
	std::vector<class Item*> mWeapons;
	std::vector<class Item*> mArmors;
};

