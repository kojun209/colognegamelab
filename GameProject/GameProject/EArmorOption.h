#pragma once

#include <string>

enum eArmorOption
{
	AO_NONE = 1,
	THORN
};

struct ArmorOption
{
	eArmorOption Option;
	std::string OptionName;
	float Value;
	std::string Description;
};

