#include <iostream>
#include <fstream>

#include "Monster.h"
#include "Player.h"
#include "EBuffFlag.h"
#include "EDebuffFlag.h"

using namespace std;

void Monster::Initialize()
{
}

void Monster::Render() const
{
	cout << "Name : " << mObjectName << endl;

	switch (mFloorNumber)
	{
	case FIRST:
		cout << "Floor : First";
		break;
	case SECOND:
		cout << "Floor : Second";
		break;
	case THIRD:
		cout << "Floor : Third";
		break;
	default:
		break;
	}

	switch (mMonsterClass)
	{
	case NORMAL:
		cout << "\tClass : Normal" << endl;
		break;
	case ELITE:
		cout << "\tClass : Elite" << endl;
		break;
	case BOSS:
		cout << "\tClass : Boss" << endl;
		break;
	default:
		break;
	}

	cout << "Level : " << mCharacterInfo.Level << "\tExp to obtain : " << mCharacterInfo.Exp << endl;
	cout << "Attack : " << mCharacterInfo.Attack << "\tDefense : " << mCharacterInfo.Defense << endl;
	cout << "HP : " << mCharacterInfo.Hp << " / " << mCharacterInfo.HpMax << endl;
	cout << "Gold to obtain : " << mGoldMin << " ~ " << mGoldMax << endl;
}

Monster* Monster::Clone() const
{
	return new Monster(*this);
}

void Monster::Save(std::ofstream& fout)
{
	Character::Save(fout);

	fout.write((char*)&mGoldMin, sizeof(int));
	fout.write((char*)&mGoldMax, sizeof(int));
	fout.write((char*)&mFloorNumber, sizeof(eFloorNumber));
	fout.write((char*)&mMonsterClass, sizeof(eMonsterClass));
	fout.write((char*)&mBuffInfo.BuffType, sizeof(eBuffFlag));
	fout.write((char*)&mBuffInfo.BuffCount, sizeof(int));
	fout.write((char*)&mDebuffInfo.DebuffType, sizeof(eDebuffFlag));
	fout.write((char*)&mDebuffInfo.DebuffCount, sizeof(int));

	unsigned int buffNameSize = mBuffInfo.BuffName.size();

	fout.write((char*)&buffNameSize, sizeof(unsigned int));
	fout.write(mBuffInfo.BuffName.c_str(), buffNameSize);

	unsigned int debuffNameSize = mDebuffInfo.DebuffName.size();

	fout.write((char*)&debuffNameSize, sizeof(unsigned int));
	fout.write(mDebuffInfo.DebuffName.c_str(), debuffNameSize);

}

void Monster::Load(std::ifstream& fin)
{
	Character::Load(fin);

	fin.read((char*)&mGoldMin, sizeof(int));
	fin.read((char*)&mGoldMax, sizeof(int));
	fin.read((char*)&mFloorNumber, sizeof(eFloorNumber));
	fin.read((char*)&mMonsterClass, sizeof(eMonsterClass));
	fin.read((char*)&mBuffInfo.BuffType, sizeof(eBuffFlag));
	fin.read((char*)&mBuffInfo.BuffCount, sizeof(int));
	fin.read((char*)&mDebuffInfo.DebuffType, sizeof(eDebuffFlag));
	fin.read((char*)&mDebuffInfo.DebuffCount, sizeof(int));

	unsigned int buffNameSize = 0;
	fin.read((char*)&buffNameSize, sizeof(unsigned int));

	constexpr int NAME_SIZE = 16;
	char buffName[NAME_SIZE];

	fin.read(buffName, buffNameSize);
	buffName[buffNameSize] = '\0';
	mBuffInfo.BuffName = buffName;

	unsigned int debuffNameSize = 0;
	fin.read((char*)&debuffNameSize, sizeof(unsigned int));

	char debuffName[NAME_SIZE];

	fin.read(debuffName, debuffNameSize);
	debuffName[debuffNameSize] = '\0';
	mDebuffInfo.DebuffName = debuffName;
}

void Monster::ActivateBuff(Player* player, Monster* monster)
{
	monster->SetBuffFlag(mBuffInfo.BuffType, mBuffInfo.BuffCount);
	
	cout << mObjectName << " used " << mBuffInfo.BuffName << endl;
}

void Monster::ActivateDebuff(Player* player, Monster* monster)
{
	player->SetDebuffFlag(mDebuffInfo.DebuffType, mDebuffInfo.DebuffCount);

	cout << mObjectName << " used " << mDebuffInfo.DebuffName << endl;
}

Monster::Monster(eObjectType objectType)
	: Character(objectType)
{
}

Monster::Monster(const Monster& other)
	: Character(other)
	, mGoldMin(other.mGoldMin)
	, mGoldMax(other.mGoldMax)
	, mFloorNumber(other.mFloorNumber)
	, mMonsterClass(other.mMonsterClass)
	, mBuffInfo(other.mBuffInfo)
	, mDebuffInfo(other.mDebuffInfo)
{
}

Monster::~Monster()
{
}