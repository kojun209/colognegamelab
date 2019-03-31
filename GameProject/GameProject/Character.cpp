#include <fstream>

#include "Character.h"

Character::Character(eObjectType objectType)
	: Object(objectType)
{
	mCharacterInfo = {};
	memset(mBuffFlag, 0, sizeof(int) * static_cast<unsigned int>(eBuffFlag::COUNT));
	memset(mDebuffFlag, 0, sizeof(int) * static_cast<unsigned int>(eDebuffFlag::COUNT));
}

Character::Character(const Character& other)
	: Object(other)
	, mCharacterInfo(other.mCharacterInfo)
{
	memset(mBuffFlag, 0, sizeof(int) * static_cast<unsigned int>(eBuffFlag::COUNT));
	memset(mDebuffFlag, 0, sizeof(int) * static_cast<unsigned int>(eDebuffFlag::COUNT));
}

Character::~Character()
{
}

void Character::Save(std::ofstream& fout)
{
	Object::Save(fout);

	fout.write((char*)&mCharacterInfo, sizeof(mCharacterInfo));
}

void Character::Load(std::ifstream& fin)
{
	Object::Load(fin);

	fin.read((char*)&mCharacterInfo, sizeof(mCharacterInfo));
}