#pragma once

#include <unordered_map>
#include <string>

#include "Singleton.h"
#include "EObjectType.h"
#include "EFloorNumber.h"
#include "EMonsterClass.h"

class Object;

class ObjectManager
{
public:
	DECLARE_SINGLETON(ObjectManager)

	void Initialize();
	Object* GetObject(const std::string& key);
	Object* CloneObject(const std::string& key);
	Object* CloneMonster(eFloorNumber floorNumber, eMonsterClass monsterClass);
	Object* CloneCard();

private:
	void createObject(const std::string& key, eObjectType type);

private:
	std::unordered_map<std::string, class Object*> mObjects;
};