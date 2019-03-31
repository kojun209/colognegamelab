#pragma once
enum class eDebuffFlag
{
	NONE,
	VULNERABLE,			// Vulnerable creatures will receive 50% more damage from attacks.
	WEAK,				// Weakened creatures deal 25 % less damage with attacks.
	DEADLY_POISON,		// Poisoned creatures lose HP at the end of their turn. Each turn, Poison is reduced by 1.
	TIME_ABSORPTION,
	COUNT
};