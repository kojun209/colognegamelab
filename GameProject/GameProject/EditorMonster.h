#pragma once

#include <vector>
#include "Singleton.h"

class EditorMonster
{
public:
	DECLARE_SINGLETON(EditorMonster)

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

private:
	std::vector<class Monster*> mMonsters;
};

