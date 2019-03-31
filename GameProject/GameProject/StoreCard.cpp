#include <iostream>
#include <fstream>

#include "StoreCard.h"
#include "Player.h"
#include "ObjectManager.h"
#include "Inventory.h"
#include "CardAttack.h"
#include "CardSkill.h"
#include "CardBuff.h"
#include "CardDebuff.h"

using namespace std;

void StoreCard::Initialize()
{
	ifstream fin("CardAttack.cda", ios_base::in | ios_base::binary);

	if (fin.is_open())
	{
		unsigned int attackCardsCount = 0;
		fin.read((char*)&attackCardsCount, sizeof(unsigned int));

		for (size_t i = 0; i < attackCardsCount; i++)
		{
			Card* card = new CardAttack(eObjectType::CARD_ATTACK);
			card->Initialize();

			card->Load(fin);
			mCards.push_back(card);
		}

		fin.close();
	}
	// ...

	fin.open("CardSkill.cds", ios_base::in | ios_base::binary);

	if (fin.is_open())
	{
		unsigned int skillCardsCount = 0;
		fin.read((char*)&skillCardsCount, sizeof(unsigned int));

		for (size_t i = 0; i < skillCardsCount; i++)
		{
			Card* card = new CardSkill(eObjectType::CARD_SKILL);
			card->Initialize();

			card->Load(fin);
			mCards.push_back(card);
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
			card->Initialize();

			card->Load(fin);
			mCards.push_back(card);
		}

		fin.close();
	}

	fin.open("CardDebuff.cdd", ios_base::in | ios_base::binary);

	if (fin.is_open())
	{
		unsigned int debuffCardsCount = 0;
		fin.read((char*)&debuffCardsCount, sizeof(unsigned int));

		for (size_t i = 0; i < debuffCardsCount; i++)
		{
			Card* card = new CardDebuff(eObjectType::CARD_DEBUFF);
			card->Initialize();

			card->Load(fin);
			mCards.push_back(card);
		}

		fin.close();
	}
}

void StoreCard::Run()
{
	Player* player = static_cast<Player*>(ObjectManager::GetInstance()->GetObject("Player"));

	while (true)
	{
		system("cls");
		cout << "===================== CARD STORE =====================" << endl;
		outputCardList();

		unsigned int back = mCards.size() + 1;
		cout << back << ". Back" << endl;
		cout << endl;
		cout << "Gold : " << player->GetGold() << endl;
		cout << "Select an item : ";

		unsigned int input = _getwche() - 48;
		if (input == 0 || input > back)
		{
			continue;
		}

		if (input == back)
		{
			return;
		}

		cout << endl << endl;

		if (player->GetGold() < mCards[input - 1]->mPriceToBuy)
		{
			cout << "Not enough Gold" << endl;
			_getwch();
			continue;
		}

		Card* card = mCards[input - 1]->Clone();
		
		player->AddCard(card);
		player->AddGold(-card->mPriceToBuy);

		cout << "Bought " << card->GetName();
		_getwch();
	}
}

StoreCard::StoreCard()
{
}

StoreCard::~StoreCard()
{
}