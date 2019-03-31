#include <iostream>
#include <fstream>

#include "EditorCard.h"
#include "ECardType.h"
#include "Card.h"
#include "CardAttack.h"
#include "CardSkill.h"
#include "CardBuff.h"
#include "CardDebuff.h"
#include "EBuffFlag.h"
#include "EDebuffFlag.h"

using namespace std;

EditorCard* EditorCard::mInstance = nullptr;

enum eEditCardMenu
{
	ADD = 1,
	DELETE,
	LIST,
	SAVE,
	LOAD,
	BACK
};

EditorCard::~EditorCard()
{
	for (auto& card : mAttackCards)
	{
		delete card;
	}

	for (auto& card : mSkillCards)
	{
		delete card;
	}

	for (auto& card : mBuffCards)
	{
		delete card;
	}
}

void EditorCard::Initialize()
{
}

void EditorCard::Run()
{
	while (true)
	{
		switch (outputMenu())
		{
		case ADD:
			add();
			break;
		case DELETE:
			remove();
			break;
		case LIST:
			list();
			break;
		case SAVE:
			save();
			break;
		case LOAD:
			load();
			break;
		case BACK:
			return;
		default:
			break;
		}
	}
}

int EditorCard::outputMenu()
{
	int input = 0;
	while (input < eEditCardMenu::ADD || input > eEditCardMenu::BACK)
	{
		system("cls");
		cout << "===================== ITEM EDITOR =====================" << endl;
		cout << "1. Add" << endl;
		cout << "2. Delete" << endl;
		cout << "3. List" << endl;
		cout << "4. Save" << endl;
		cout << "5. Load" << endl;
		cout << "6. Back" << endl;
		cout << "Select an option : ";

		input = _getwche() - 48;
	}

	return input;
}

void EditorCard::add()
{
	int input = 0;
	while (input < eCardType::CT_ATTACK || input > eCardType::CT_COUNT)
	{
		system("cls");
		cout << "===================== Add =====================" << endl;
		cout << "1. Attack" << endl;
		cout << "2. Skill" << endl;
		cout << "3. Buff" << endl;
		cout << "4. Debuff" << endl;
		cout << "5. Back" << endl;
		cout << "Select an item type : ";

		input = _getwche() - 48;
	}

	if (input == eCardType::CT_COUNT)
	{
		return;
	}

	system("cls");

	Card* card = nullptr;

	switch (input)
	{
	case eCardType::CT_ATTACK:
		card = new CardAttack(eObjectType::CARD_ATTACK);
		cout << "===================== ADD ATTACK CARD =====================" << endl;
		break;
	case eCardType::CT_SKILL:
		card = new CardSkill(eObjectType::CARD_SKILL);
		cout << "===================== ADD SKILL CARD =====================" << endl;
		break;
	case eCardType::CT_BUFF:
		card = new CardBuff(eObjectType::CARD_BUFF);
		cout << "===================== ADD BUFF CARD =====================" << endl;
		break;
	case eCardType::CT_DEBUFF:
		card = new CardBuff(eObjectType::CARD_DEBUFF);
		cout << "===================== ADD DEBUFF CARD =====================" << endl;
		break;
	default:
		break;
	}

	card->Initialize();

	cout << "Name : ";

	constexpr int NAME_SIZE = 32;
	char name[NAME_SIZE];
	cin.getline(name, NAME_SIZE);
	card->SetName(name);

	cout << "Description : ";

	constexpr int DESCRIPTION_SIZE = 128;
	char description[DESCRIPTION_SIZE] = {};
	cin.getline(description, DESCRIPTION_SIZE);

	int energyCost, priceToBuy, priceToSell;

	inputInt("Energy cost", energyCost);
	inputInt("Price to buy", priceToBuy);
	inputInt("Price to sell", priceToSell);

	card->SetCardInfo(static_cast<eCardType>(input), energyCost, description, priceToBuy, priceToSell);

	if (input == eCardType::CT_ATTACK)
	{
		float playerAttackValue, weaponAttackValue;
		int attackCount, debuffCount;

		inputFloat("Player Attack", playerAttackValue);
		inputFloat("Weapon Attack", weaponAttackValue);
		inputInt("Attack Count", attackCount);

		cout << "Debuff" << endl;
		cout << "0. None" << endl;
		cout << "1. Vulnerable" << endl;
		cout << "2. Weak" << endl;
		cout << "Select an option : ";

		int debuff = -1;
		while (debuff < static_cast<int>(eDebuffFlag::NONE) || debuff > static_cast<int>(eDebuffFlag::TIME_ABSORPTION))
		{
			debuff = _getwch() - 48;
		}
		cout << debuff << endl;

		inputInt("Debuff Count", debuffCount);

		static_cast<CardAttack*>(card)->SetAttackCardInfo(playerAttackValue, weaponAttackValue, attackCount, static_cast<eDebuffFlag>(debuff), debuffCount);
	}
	else if (input == eCardType::CT_SKILL)
	{
		int hp, energy;

		inputInt("HP", hp);
		inputInt("Energy", energy);

		static_cast<CardSkill*>(card)->SetSkillCardInfo(hp, energy);
	}
	else if (input == eCardType::CT_BUFF)
	{
		int buffCount;

		cout << "Buff" << endl;
		cout << "1. Strength" << endl;
		cout << "2. Block" << endl;
		cout << "3. Catalyst" << endl;
		cout << "Select an option : ";

		int buff = -1;
		while (buff <= static_cast<int>(eBuffFlag::NONE) || buff > static_cast<int>(eBuffFlag::CATALYST))
		{
			buff = _getwch() - 48;
		}
		cout << buff << endl;

		inputInt("Buff Count", buffCount);

		static_cast<CardBuff*>(card)->SetBuffCardInfo(static_cast<eBuffFlag>(buff), buffCount);
	}
	else
	{
		int debuffCount;

		cout << "Debuff" << endl;
		cout << "1. Vulnerable" << endl;
		cout << "2. Weak" << endl;
		cout << "3. Deadly Poison" << endl;
		cout << "4. Time Absorption" << endl;
		cout << "Select an option : ";

		int debuff = -1;
		while (debuff <= static_cast<int>(eDebuffFlag::NONE) || debuff > static_cast<int>(eDebuffFlag::TIME_ABSORPTION))
		{
			debuff = _getwch() - 48;
		}
		cout << debuff << endl;

		inputInt("Debuff Count", debuffCount);

		static_cast<CardDebuff*>(card)->SetDebuffCardInfo(static_cast<eDebuffFlag>(debuff), debuffCount);
	}

	switch (input)
	{
	case eCardType::CT_ATTACK:
		mAttackCards.push_back(card);
		break;
	case eCardType::CT_SKILL:
		mSkillCards.push_back(card);
		break;
	case eCardType::CT_BUFF:
		mBuffCards.push_back(card);
		break;
	case eCardType::CT_DEBUFF:
		mDebuffCards.push_back(card);
		break;
	default:
		break;
	}

	cout << endl << "Added successfully";
	_getwch();
}

void EditorCard::remove()
{
	int input = 0;
	while (input < eCardType::CT_ATTACK || input > eCardType::CT_COUNT)
	{
		system("cls");
		cout << "===================== DELETE =====================" << endl;
		cout << "1. Attack" << endl;
		cout << "2. Skill" << endl;
		cout << "3. Buff" << endl;
		cout << "4. Debuff" << endl;
		cout << "5. Back" << endl;
		cout << "Select a card type : ";

		input = _getwche() - 48;
	}

	if (input == eCardType::CT_COUNT)
	{
		return;
	}

	if (input == eCardType::CT_ATTACK)
	{
		while (true)
		{
			system("cls");
			cout << "===================== DELETE ATTACK =====================" << endl;
			size_t i;
			for (i = 0; i < mAttackCards.size(); i++)
			{
				cout << i + 1 << ". ";
				mAttackCards[i]->Render();
				cout << endl;
			}

			cout << i + 1 << ". Back" << endl;
			cout << "Select a number to delete : ";

			unsigned int input = 0;
			while (input == 0 || input > mAttackCards.size() + 1)
			{
				input = _getwch() - 48;
			}

			if (input == mAttackCards.size() + 1)
			{
				return;
			}

			cout << input;

			vector<Card*>::iterator it;
			it = mAttackCards.begin();

			it += (input - 1);
			mAttackCards.erase(it);

			cout << endl << endl << "Deleted successfully";
			_getwche();
		}
	}
	else if (input == eCardType::CT_SKILL)
	{
		while (true)
		{
			system("cls");
			cout << "===================== DELETE SKILL =====================" << endl;
			size_t i;
			for (i = 0; i < mSkillCards.size(); i++)
			{
				cout << i + 1 << ". ";
				mSkillCards[i]->Render();
				cout << endl;
			}

			cout << i + 1 << ". Back" << endl;
			cout << "Select a number to delete : ";

			unsigned int input = 0;
			while (input == 0 || input > mSkillCards.size() + 1)
			{
				input = _getwch() - 48;
			}

			if (input == mSkillCards.size() + 1)
			{
				return;
			}

			cout << input;

			vector<Card*>::iterator it;
			it = mSkillCards.begin();

			it += (input - 1);
			mSkillCards.erase(it);

			cout << endl << endl << "Deleted successfully";
			_getwche();
		}
	}
	else if (input == eCardType::CT_BUFF)
	{
		while (true)
		{
			system("cls");
			cout << "===================== DELETE BUFF =====================" << endl;
			size_t i;
			for (i = 0; i < mBuffCards.size(); i++)
			{
				cout << i + 1 << ". ";
				mBuffCards[i]->Render();
				cout << endl;
			}

			cout << i + 1 << ". Back" << endl;
			cout << "Select a number to delete : ";

			unsigned int input = 0;
			while (input == 0 || input > mBuffCards.size() + 1)
			{
				input = _getwch() - 48;
			}

			if (input == mBuffCards.size() + 1)
			{
				return;
			}

			cout << input;

			vector<Card*>::iterator it;
			it = mBuffCards.begin();

			it += (input - 1);
			mBuffCards.erase(it);

			cout << endl << endl << "Deleted successfully";
			_getwche();
		}
	}
	else
	{
		while (true)
		{
			system("cls");
			cout << "===================== DELETE DEBUFF =====================" << endl;
			size_t i;
			for (i = 0; i < mDebuffCards.size(); i++)
			{
				cout << i + 1 << ". ";
				mDebuffCards[i]->Render();
				cout << endl;
			}

			cout << i + 1 << ". Back" << endl;
			cout << "Select a number to delete : ";

			unsigned int input = 0;
			while (input == 0 || input > mDebuffCards.size() + 1)
			{
				input = _getwch() - 48;
			}

			if (input == mDebuffCards.size() + 1)
			{
				return;
			}

			cout << input;

			vector<Card*>::iterator it;
			it = mDebuffCards.begin();

			it += (input - 1);
			mDebuffCards.erase(it);

			cout << endl << endl << "Deleted successfully";
			_getwche();
		}
	}
}

void EditorCard::list()
{
	system("cls");
	cout << "===================== Attack =====================" << endl;
	for (size_t i = 0; i < mAttackCards.size(); i++)
	{
		cout << i + 1 << ". ";
		mAttackCards[i]->Render();
		cout << endl;
	}

	cout << "===================== Skill =====================" << endl;
	for (size_t i = 0; i < mSkillCards.size(); i++)
	{
		cout << i + 1 << ". ";
		mSkillCards[i]->Render();
		cout << endl;
	}

	cout << "===================== Buff =====================" << endl;
	for (size_t i = 0; i < mBuffCards.size(); i++)
	{
		cout << i + 1 << ". ";
		mBuffCards[i]->Render();
		cout << endl;
	}

	cout << "===================== Debuff =====================" << endl;
	for (size_t i = 0; i < mDebuffCards.size(); i++)
	{
		cout << i + 1 << ". ";
		mDebuffCards[i]->Render();
		cout << endl;
	}

	_getwch();
}

void EditorCard::save()
{
	ofstream fout("CardAttack.cda", ios_base::out | ios_base::binary);

	if (fout.is_open())
	{
		unsigned int attackCardsCount = mAttackCards.size();
		fout.write((char*)&attackCardsCount, sizeof(unsigned int));

		for (size_t i = 0; i < attackCardsCount; i++)
		{
			mAttackCards[i]->Save(fout);
		}

		fout.close();
	}
	// ...

	fout.open("CardSkill.cds", ios_base::out | ios_base::binary);

	if (fout.is_open())
	{
		unsigned int skillCardsCount = mSkillCards.size();
		fout.write((char*)&skillCardsCount, sizeof(unsigned int));;

		for (size_t i = 0; i < skillCardsCount; i++)
		{
			mSkillCards[i]->Save(fout);
		}

		fout.close();
	}

	fout.open("CardBuff.cdb", ios_base::out | ios_base::binary);

	if (fout.is_open())
	{
		unsigned int buffCardsCount = mBuffCards.size();
		fout.write((char*)&buffCardsCount, sizeof(unsigned int));;

		for (size_t i = 0; i < buffCardsCount; i++)
		{
			mBuffCards[i]->Save(fout);
		}

		fout.close();
	}

	fout.open("CardDebuff.cdd", ios_base::out | ios_base::binary);

	if (fout.is_open())
	{
		unsigned int debuffCardsCount = mDebuffCards.size();
		fout.write((char*)&debuffCardsCount, sizeof(unsigned int));;

		for (size_t i = 0; i < debuffCardsCount; i++)
		{
			mDebuffCards[i]->Save(fout);
		}

		fout.close();
	}

	cout << endl << "Save complete" << endl;
	_getwch();
}

void EditorCard::load()
{
	for (auto& attackCard : mAttackCards)
	{
		delete attackCard;
	}
	mAttackCards.clear();

	for (auto& skillCard : mSkillCards)
	{
		delete skillCard;
	}
	mSkillCards.clear();

	for (auto& buffCard : mBuffCards)
	{
		delete buffCard;
	}
	mBuffCards.clear();

	for (auto& debuffCard : mDebuffCards)
	{
		delete debuffCard;
	}
	mDebuffCards.clear();

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
			mAttackCards.push_back(card);
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
			card->Initialize();

			card->Load(fin);
			mSkillCards.push_back(card);
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
			mBuffCards.push_back(card);
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
			mDebuffCards.push_back(card);
		}

		fin.close();
	}

	cout << endl << "Load complete" << endl;
	_getwch();
}

void EditorCard::inputInt(const char * property, int & data)
{
	while (true)
	{
		cout << property << " : ";
		cin >> data;

		if (cin.fail())
		{
			cout << "Invalid Input" << endl;
			cin.clear();
			cin.ignore(LLONG_MAX, '\n');
			continue;
		}

		cin.ignore(LLONG_MAX, '\n');
		return;
	}
}

void EditorCard::inputFloat(const char * property, float & data)
{
	while (true)
	{
		cout << property << " : ";
		cin >> data;

		if (cin.fail())
		{
			cout << "Invalid Input" << endl;
			cin.clear();
			cin.ignore(LLONG_MAX, '\n');
			continue;
		}

		cin.ignore(LLONG_MAX, '\n');
		return;
	}
}
