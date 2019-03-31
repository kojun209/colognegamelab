#include <cassert>
#include <fstream>

#include "ObjectManager.h"
#include "Player.h"
#include "Monster.h"
#include "CardAttack.h"
#include "CardSkill.h"
#include "CardBuff.h"

using namespace std;

ObjectManager* ObjectManager::mInstance = nullptr;

ObjectManager::~ObjectManager()
{
	for (auto& object : mObjects)
	{
		delete object.second;
	}
}

void ObjectManager::Initialize()
{
	ifstream fin("MonsterList.mtl", ios_base::in | ios_base::binary);

	if (fin.is_open())
	{
		unsigned int monstersCount = 0;
		fin.read((char*)&monstersCount, sizeof(unsigned int));

		for (size_t i = 0; i < monstersCount; i++)
		{
			Monster* monster = new Monster(eObjectType::MONSTER);
			monster->Load(fin);
			mObjects.insert(make_pair(monster->GetName(), monster));
		}

		fin.close();
	}

	fin.open("CardAttack.cda", ios_base::in | ios_base::binary);

	if (fin.is_open())
	{
		unsigned int attackCardsCount = 0;
		fin.read((char*)&attackCardsCount, sizeof(unsigned int));

		for (size_t i = 0; i < attackCardsCount; i++)
		{
			Card* card = new CardAttack(eObjectType::CARD_ATTACK);
			card->Load(fin);
			mObjects.insert(make_pair(card->GetName(), card));
		}

		fin.close();
	}

	fin.open("CardSkill.cds", ios_base::in | ios_base::binary);

	if (fin.is_open())
	{
		unsigned int skillCardsCount = 0;
		fin.read((char*)&skillCardsCount, sizeof(unsigned int));

		for (size_t i = 0; i < skillCardsCount; i++)
		{
			Card* card = new CardSkill(eObjectType::CARD_SKILL);
			card->Load(fin);
			mObjects.insert(make_pair(card->GetName(), card));
		}

		fin.close();
	}

	fin.open("CardBuff.cdb", ios_base::in | ios_base::binary);

	if (fin.is_open())
	{
		unsigned int buffCardsCount = 0;
		fin.read((char*)&buffCardsCount, sizeof(unsigned int));

		for (size_t i = 0; i < buffCardsCount; i++)
		{
			Card* card = new CardBuff(eObjectType::CARD_BUFF);
			card->Load(fin);
			mObjects.insert(make_pair(card->GetName(), card));
		}

		fin.close();
	}

	createObject("Player", eObjectType::PLAYER);
}

Object* ObjectManager::GetObject(const std::string& key)
{
	auto it = mObjects.find(key);

	assert(it != mObjects.end());	// Object not found

	return it->second;
}

Object* ObjectManager::CloneObject(const std::string& key)
{
	Object* origin = GetObject(key);	// GetObject doesn't return NULL

	return origin->Clone();
}

Object* ObjectManager::CloneMonster(eFloorNumber floorNumber, eMonsterClass monsterClass)
{
	std::vector<Monster*> monsters;

	for (auto& object : mObjects)
	{
		if (object.second->GetObjectType() == eObjectType::MONSTER)
		{
			Monster* monster = static_cast<Monster*>(object.second);
			if (monster->GetFloorNumber() == floorNumber && monster->GetMonsterClass() == monsterClass)
			{
				monsters.push_back(monster);
			}
		}
	}

	assert(!monsters.empty());

	int index = rand() % monsters.size();
	return monsters[index]->Clone();
}

Object* ObjectManager::CloneCard()
{
	std::vector<Card*> cards;

	for (auto& object : mObjects)
	{
		if (object.second->GetObjectType() == eObjectType::CARD_ATTACK || object.second->GetObjectType() == eObjectType::CARD_BUFF
			|| object.second->GetObjectType() == eObjectType::CARD_DEBUFF || object.second->GetObjectType() == eObjectType::CARD_SKILL)
		{
			Card* card = static_cast<Card*>(object.second);
			cards.push_back(card);
		}
	}

	int index = rand() % cards.size();
	return cards[index]->Clone();
}


void ObjectManager::createObject(const std::string& key, eObjectType type)
{
	Object* object = nullptr;

	switch (type)
	{
	case eObjectType::PLAYER:
		object = new Player(eObjectType::PLAYER);
		break;
	case eObjectType::MONSTER:
		object = new Monster(eObjectType::MONSTER);
		break;
	default:
		break;
	}

	object->Initialize();
	mObjects.insert(std::make_pair(key, object));
}
