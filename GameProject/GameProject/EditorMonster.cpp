#include <iostream>
#include <fstream>

#include "Monster.h"
#include "EditorMonster.h"
#include "EFloorNumber.h"

using namespace std;

EditorMonster* EditorMonster::mInstance = nullptr;

enum eEditMonsterMenu
{
	ADD = 1,
	DELETE,
	LIST,
	SAVE,
	LOAD,
	BACK
};

EditorMonster::~EditorMonster()
{
	for (auto& monster : mMonsters)
	{
		delete monster;
	}
}

void EditorMonster::Initialize()
{
}

void EditorMonster::Run()
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

int EditorMonster::outputMenu()
{
	int input = 0;
	while (input < eEditMonsterMenu::ADD || input > eEditMonsterMenu::BACK)
	{
		system("cls");
		cout << "===================== MONSTER EDITOR =====================" << endl;
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

void EditorMonster::add()
{
	Monster* monster = new Monster(eObjectType::MONSTER);
	monster->Initialize();

	system("cls");
	cout << "===================== ADD =====================" << endl;
	cout << "Name : ";

	constexpr int NAME_SIZE = 32;
	char name[NAME_SIZE];
	cin.getline(name, NAME_SIZE);
	monster->SetName(name);

	int attack, defense, hp, level, exp;

	inputInt("Attack", attack);
	inputInt("Defense", defense);
	inputInt("HP", hp);
	inputInt("Level", level);
	inputInt("Exp to obtain", exp);
	monster->SetCharacterInfo(attack, defense, hp, level, exp);

	int goldMin, goldMax;

	inputInt("Gold Min", goldMin);
	inputInt("Gold Max", goldMax);
	monster->SetDropGold(goldMin, goldMax);

	cout << endl;
	cout << "Floor" << "\t1. First" << "  2. Second" << "  3. Third" << endl;
	cout << "Select an option : ";

	int input = 0;
	while (input < eFloorNumber::FIRST || input > eFloorNumber::THIRD)
	{
		input = _getwch() - 48;
	}
	cout << input << endl;

	monster->SetFloorNumber(static_cast<eFloorNumber>(input));

	cout << "Class" << "\t1. Normal" << "  2. Elite" << "  3. Boss" << endl;
	cout << "Select an option : ";

	input = 0;
	while (input < eMonsterClass::NORMAL || input > eMonsterClass::BOSS)
	{
		input = _getwch() - 48;
	}
	cout << input << endl;

	monster->SetMonsterClass(static_cast<eMonsterClass>(input));
	mMonsters.push_back(monster);

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

	monster->SetBuffInfo(static_cast<eBuffFlag>(buff), buffCount);

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

	monster->SetDebuffInfo(static_cast<eDebuffFlag>(debuff), debuffCount);

	cout << endl << "Added successfully";
	_getwch();
}

void EditorMonster::remove()
{
	system("cls");
	cout << "===================== DELETE =====================" << endl;

	int i = 1;
	for (auto& monster : mMonsters)
	{
		cout << i << ". ";
		monster->Render();
		cout << endl;
		i++;
	}

	cout << i << ". Back" << endl;
	cout << "Select a number to delete : ";

	unsigned int input = 0;
	while (input == 0 || input > mMonsters.size() + 1)
	{
		input = _getwch() - 48;
	}

	if (input == mMonsters.size() + 1)
	{
		return;
	}

	cout << input;

	vector<Monster*>::iterator it;
	it = mMonsters.begin();
	
	it += (input - 1);
	mMonsters.erase(it);

	cout << endl << endl << "Deleted successfully";
	_getwche();
}

void EditorMonster::list()
{
	system("cls");
	cout << "===================== LIST =====================" << endl;

	int i = 1;
	for (auto& monster : mMonsters)
	{
		cout << i << ". ";
		monster->Render();
		cout << endl;
		i++;
	}

	_getwch();
}

void EditorMonster::save()
{
	ofstream fout("MonsterList.mtl", ios_base::out | ios_base::binary);

	if (fout.is_open())
	{
		int monstersCount = mMonsters.size();
		fout.write((const char*)&monstersCount, sizeof(int));

		for (int i = 0; i < monstersCount; i++)
		{
			mMonsters[i]->Save(fout);
		}
	}
	
	cout << endl << "Save complete" << endl;
	_getwch();
}

void EditorMonster::load()
{
	for (auto& monster : mMonsters)
	{
		delete monster;
	}

	mMonsters.clear();

	ifstream fin("MonsterList.mtl", ios_base::in | ios_base::binary);

	if (fin.is_open())
	{
		int monstersCount = 0;
		fin.read((char*)&monstersCount, sizeof(int));

		for (int i = 0; i < monstersCount; i++)
		{
			Monster* monster = new Monster(eObjectType::MONSTER);
			monster->Initialize();

			monster->Load(fin);
			mMonsters.push_back(monster);
		}
	}

	cout << endl << "Load complete" << endl;
	_getwch();
}

void EditorMonster::inputInt(const char* property, int& data)
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