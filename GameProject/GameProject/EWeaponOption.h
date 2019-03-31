#pragma once
#include <string>
enum eWeaponOption
{
	WO_NONE = 1,
	IGNORE_DEFENSE
};

struct WeaponOption
{
	eWeaponOption Option;
	std::string OptionName;
	float Value;
	std::string Description;
};