#pragma once
#include "Singleton.h"

class EditorCore
{
public:
	DECLARE_SINGLETON(EditorCore)

	void Initialize();
	void Run();

private:
	int outputMenu();
};

