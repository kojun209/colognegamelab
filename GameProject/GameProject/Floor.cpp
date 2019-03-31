#include <algorithm>
#include <cassert>
#include <iostream>

#include "Floor.h"
#include "Player.h"
#include "Monster.h"
#include "FixedVector.h"
#include "Card.h"
#include "ObjectManager.h"
#include "EBuffType.h"
#include "Core.h"

int Floor::mKilledMonstersCount = 1;

Floor::Floor()
{
}

Floor::~Floor()
{
}

void Floor::Initialize()
{

}

void Floor::Run()
{
	Player* player = static_cast<Player*>(ObjectManager::GetInstance()->GetObject("Player"));
	Monster* monster = nullptr;
	eMonsterClass monsterClass = OutputMonsterClassMenu();	// 1. Normal	2. Elite

	if (monsterClass == eMonsterClass::BOSS)	// == 3. Back to the main menu
	{
		return;
	}

	if (mKilledMonstersCount % 10 != 0)
	{
		monster = static_cast<Monster*>(ObjectManager::GetInstance()
			->CloneMonster(mFloorNumber, monsterClass));
	}
	else
	{
		monster = static_cast<Monster*>(ObjectManager::GetInstance()
			->CloneMonster(mFloorNumber, eMonsterClass::BOSS));
	}

	mDrawPile = static_cast<Player*>(ObjectManager::GetInstance()
		->GetObject("Player"))->GetCards();

	shuffleCards(mDrawPile);

	while (true)
	{
		eCombatResult combatResult = handleCombat(player, monster);

		if (combatResult == eCombatResult::PLAYER_DIE)
			// ...
		{
			cout << endl << "You died" << endl;
			_getwch();
			delete monster;
			system("exit");
		}

		if (combatResult == eCombatResult::MONSTER_DIE)
		{
			int exp = monster->GetCharacterInfo().Exp;
			int dropGold = monster->GetDropGold();

			cout << endl << monster->GetName() << " dies." << endl << endl;
			_getwch();

			cout << player->GetName() << " obtained " << exp << " exp" << endl;
			cout << player->GetName() << " obtained " << dropGold << " gold" << endl;
			_getwch();

			player->AddGold(dropGold);

			if (player->AddExp(exp))	// return true if level up 
			{
				player->LevelUp();
				player->AddLevelUpStatus(Core::GetInstance()->GetLevelUpInfo(player->GetClassType()));

				cout << "Level Up!" << endl;
				_getwch();
			}
			cout << endl;

			int input = 0;
			int count = 0;

			while (input != 1 && count < 3)
			{
				input = 0;
				Card* card = static_cast<Card*>(ObjectManager::GetInstance()->CloneCard());

				card->Render();
				cout << endl;

				cout << "Do you want to pick this card?" << endl;
				cout << "1. Yes" << endl;
				cout << "2. No" << endl;
				cout << "Select an option : ";
				
				while (input < 1 || input > 2 && count < 3)
				{
					input = _getwch() - 48;
				}

				cout << input;
				cout << endl << endl;

				if (input == 1)
				{
					cout << "Picked the card" << endl;
					player->AddCard(card);
					_getwch();
				}
				else
				{
					delete card;
					count++;
				}
			}

			mKilledMonstersCount++;

			if (mKilledMonstersCount % 10 == 0)
			{
				cout << endl;
				cout << "The door to the boss opened" << endl;
				_getwch();
			}

			delete monster;

			return;
		}
	}
}

eMonsterClass Floor::OutputMonsterClassMenu()
{
	int input = 0;
	while (input < eMonsterClass::NORMAL || input > eMonsterClass::BOSS)	// eMonsterClass::BOSS == 3. Back
	{
		system("cls");
		cout << "1. Normal" << endl;
		cout << "2. Elite" << endl;
		cout << "3. Back" << endl;
		cout << "Select a monster class : ";

		input = _getwche() - 48;
	}

	return static_cast<eMonsterClass>(input);
}

eCombatResult Floor::handleCombat(Player* player, Monster* monster)
{
	while (mHandOfCards.GetSize() < (size_t)(eCardDeckInfo::HAND_OF_CARDS_MAX))
	{
		mHandOfCards.Add(drawCard());
	}
	// ...

	// decide monster's intention and calculate monster's attack damage...
	eBuffType buffType;

	const float BUFF_PROBABILITY = 15.f, DEBUFF_PROBABILITY = 30.f;
	float number = rand() % 10000 / 100.f;

	if (number < BUFF_PROBABILITY)
	{
		buffType = eBuffType::BUFF;
	}	// ...
	else if (number < DEBUFF_PROBABILITY)
	{
		buffType = eBuffType::DEBUFF;
	}
	else
	{
		buffType = eBuffType::NONE;
	}

	// calculate monster's attack damage
	int monsterAttackDamage;
	float percent = (rand() % 11 + 5) / (float)10;
	monsterAttackDamage = (int)(monster->GetAttack() * percent);	// == 50% ~ 150% of monster's attack

	if (player->GetDebuffFlag(eDebuffFlag::TIME_ABSORPTION))
	{
		cout << "Your time is absorbed. You cannot do anything." << endl;
		cout << endl;
		_getwch();

		goto MONSTERS_TURN;
	}

	eCombatResult combatResult;

	while (true)	// Player's turn
	{
		// render player's info, monster's info and monster's intention
		system("cls");
		cout << "===================== FIRST FLOOR =====================" << endl;
		player->Render();
		cout << endl;
		monster->Render();
		cout << endl;

		switch (buffType)
		{
		case eBuffType::NONE:
			cout << "This enemy intends to Attack for " << monsterAttackDamage << " damage" << endl;
			break;
		case eBuffType::BUFF:
			cout << "This enemy intends to use a Buff" << endl;
			break;
		case eBuffType::DEBUFF:
			cout << "This enemy intends to use a Debuff" << endl;
			break;
		default:
			break;
		}
		cout << endl;

		size_t i;
		for (i = 0; i < mHandOfCards.GetSize(); i++)
		{
			cout << i + 1 << ". ";
			mHandOfCards[i]->Render();
			cout << endl;
		}

		int turnEnd = i + 1;
		cout << turnEnd << ". Turn End" << endl;
		cout << endl;
		cout << "Energy : " << player->GetEnergy() << "\tSelect a card : ";

		int input = 0;
		while (input < 1 || input > turnEnd)
		{
			input = _getwch() - 48;
		}
		cout << input << endl << endl;

		if (input == turnEnd)
		{
			break;
		}

		int cardIndex = input - 1;
		Card* card = mHandOfCards[cardIndex];

		if (!card->CanAfford(player))
		{
			continue;
		}

		mHandOfCards.RemoveByIndex(cardIndex);

		combatResult = card->ActivateCard(player, monster);

		if (combatResult == eCombatResult::PLAYER_DIE || combatResult == eCombatResult::MONSTER_DIE)
		{
			break;
		}
		
		mDiscardPile.Add(card);	// move the card to Discard Pile
		player->SubtractEnergy(card->GetCost());
	}

	if (combatResult == eCombatResult::PLAYER_DIE)
	{
		return eCombatResult::PLAYER_DIE;
	}

	if (combatResult == eCombatResult::MONSTER_DIE)
	{
		player->SetEnergy(INITIAL_ENERGY);
		mHandOfCards.Clear();
		player->ClearBuffFlag();
		player->ClearDebuffFlag();

		return eCombatResult::MONSTER_DIE;
	}

	// when player's turn ends, move all the cards from the hand to to Discard Pile 
	while (!mHandOfCards.IsEmpty())
	{
		mDiscardPile.Add(mHandOfCards.GetLast());
		mHandOfCards.RemoveLast();
	}

	// handle Monster's turn
MONSTERS_TURN:
	if (buffType == eBuffType::BUFF)
	{
		monster->ActivateBuff(player, monster);
	}
	else if (buffType == eBuffType::DEBUFF)
	{
		monster->ActivateDebuff(player, monster);
	}
	else
	{
		int playerDefense = player->GetDefense();

		if (player->GetBuffFlag(eBuffFlag::BLOCK))
		{
			playerDefense = static_cast<int>(playerDefense * 1.2f);
		}

		monsterAttackDamage = monsterAttackDamage - playerDefense;
		monsterAttackDamage = monsterAttackDamage < 1 ? 1 : monsterAttackDamage;

		player->SubtractDamage(monsterAttackDamage);

		cout << monster->GetName() << " attacks " << player->GetName() << "!" << endl;
		cout << monster->GetName() << " hits for " << monsterAttackDamage << " damage to " << player->GetName() << "." << endl;

		// return false if player has no armor
		if (player->GetArmor() && player->GetArmor()->GetArmorOption().Option == eArmorOption::THORN)
		{
			monster->SubtractDamage(monsterAttackDamage);
			cout << endl;
			cout << monster->GetName() << " got damaged " << monsterAttackDamage << "by Thorn." << endl;
		}
	}
	_getwch();
	cout << endl;

	if (player->GetDebuffFlag(eDebuffFlag::DEADLY_POISON))
	{
		int poisonDamage = player->GetDebuffFlag(eDebuffFlag::DEADLY_POISON);

		if (monster->GetBuffFlag(eBuffFlag::CATALYST))
		{
			poisonDamage *= 2;
		}

		player->SubtractDamage(poisonDamage);
		cout << player->GetName() << " got " << poisonDamage << " damage by Deadly Poison." << endl;
		_getwch();
	}

	if (player->IsDead())
	{
		return eCombatResult::PLAYER_DIE;
	}

	player->SetEnergy(INITIAL_ENERGY);
	player->DecreaseBuffFlag();	// At the end of monster's turn decrease buff and debuff flags by 1
	player->DecreaseDebuffFlag();
	mHandOfCards.Clear();

	return eCombatResult::NONE;
}

void Floor::shuffleCards(FixedVector<Card*, eCardDeckInfo::CARD_DECK_MAX>& cards)
{
	size_t size = cards.GetSize();
	for (size_t i = 0; i < 100; i++)
	{
		int index1 = rand() % size;
		int index2 = rand() % size;

		Card* temp = cards[index1];
		cards[index1] = cards[index2];
		cards[index2] = temp;
	}
}

Card* Floor::drawCard()
{
	// if Draw Pile is empty, shuffle cards in Discard Pile and move them to Draw Pile
	if (mDrawPile.IsEmpty())	// mDrawPile is an object of class FixedVector
	{
		shuffleCards(mDiscardPile);

		while (!mDiscardPile.IsEmpty())
		{
			mDrawPile.Add(mDiscardPile.GetLast());
			mDiscardPile.RemoveLast();
		}
	}

	Card* card = mDrawPile.GetLast();	// get and remove a card from the back to reduce operations
	mDrawPile.RemoveLast();

	return card;
}
