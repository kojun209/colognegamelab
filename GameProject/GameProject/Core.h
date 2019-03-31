#pragma once

#include "Singleton.h"
#include "LevelUpTable.h"
#include "EClassType.h"

class Core
{
public:
	DECLARE_SINGLETON(Core)

	void Initialize();
	void Run();
	LevelUpInfo GetLevelUpInfo(eClassType classType);

private:
	int outputMainMenu();
	void setLevelUpInfo();
	LevelUpInfo createLevelUpInfo(int attack, int defense, int hp);

private:
	LevelUpInfo mLevelUpInfo[eClassType::CLASS_COUNT - 1];
};
