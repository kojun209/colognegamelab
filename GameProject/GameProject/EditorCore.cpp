#include <iostream>

#include "EditorCore.h"
#include "EditorMonster.h"
#include "EditorItem.h"
#include "EditorCard.h"

using namespace std;

EditorCore* EditorCore::mInstance = nullptr;

enum eEditMenu
{
	MONSTER = 1,
	ITEM,
	CARD,
	EXIT
};

EditorCore::~EditorCore()
{
	EditorMonster::DestroyInstance();
	EditorItem::DestroyInstance();
	EditorCard::DestroyInstance();
}

void EditorCore::Initialize()
{
	EditorMonster::GetInstance()->Initialize();
	EditorItem::GetInstance()->Initialize();
	EditorCard::GetInstance()->Initialize();
}

void EditorCore::Run()
{
	while (true)
	{
		switch (outputMenu())
		{
		case MONSTER:
			EditorMonster::GetInstance()->Run();
			break;
		case ITEM:
			EditorItem::GetInstance()->Run();
			break;
		case CARD:
			EditorCard::GetInstance()->Run();
			break;
		case EXIT:
			return;
		default:
			break;
		}
	}
}

int EditorCore::outputMenu()
{
	int input = 0;
	while (input < eEditMenu::MONSTER || input > eEditMenu::EXIT)
	{
		system("cls");
		cout << "===================== Edit =====================" << endl;
		cout << "1. Monster" << endl;
		cout << "2. Item" << endl;
		cout << "3. Card" << endl;
		cout << "4. Exit" << endl;
		cout << "Select an option : ";

		input = _getwche() - 48;
	}

	return input;
}

