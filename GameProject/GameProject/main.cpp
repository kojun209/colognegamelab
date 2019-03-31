#include <stdlib.h>
#include <time.h>
#include <iostream>

#include "Core.h"
#include "EditorCore.h"

using namespace std;

enum eGameMode
{
	PLAY = 1,
	EDIT,
	EXIT
};

int main()
{
	srand((unsigned int)time(NULL));
	
	int input = 0;
	while (input < eGameMode::PLAY || input > eGameMode::EXIT)
	{
		system("cls");
		cout << "1. Play" << endl;
		cout << "2. Edit" << endl;
		cout << "3. Exit" << endl;
		cout << "Select an option : ";

		input = _getwche() - 48;
	}

	switch (input)
	{
	case eGameMode::PLAY:
		Core::GetInstance()->Initialize();

		Core::GetInstance()->Run();

		Core::DestroyInstance();
		break;
	case eGameMode::EDIT:
		EditorCore::GetInstance()->Initialize();

		EditorCore::GetInstance()->Run();

		EditorCore::DestroyInstance();
		break;
	case eGameMode::EXIT:
		return 0;
	default:
		break;
	}

	return 0;
}