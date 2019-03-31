#pragma once

#include <vector>

#include "Singleton.h"

class EditorCard
{
public:
	DECLARE_SINGLETON(EditorCard)

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
	std::vector<class Card*> mAttackCards;
	std::vector<class Card*> mSkillCards;
	std::vector<class Card*> mBuffCards;
	std::vector<class Card*> mDebuffCards;
};

