#pragma once
enum class eBuffFlag
{
	NONE,
	STRENGTH,	// increases character attack damage by 50%
	BLOCK,		// increases character defense by 50%
	DRAW_CARD,
	CATALYST,	// makes damage from Deadly Poison double
	COUNT
};