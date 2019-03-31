#pragma once

const int MAX_LEVEL = 10;
static const int LEVEL_UP_TABLE[MAX_LEVEL] = { 4000, 10000, 20000, 35000, 52000, 72000, 90000, 130000, 170000, 250000 };

struct LevelUpInfo
{
	int Attack;
	int Defense;
	int Hp;
};
