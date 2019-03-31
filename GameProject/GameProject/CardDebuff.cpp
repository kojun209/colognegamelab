#include <iostream>
#include <fstream>

#include "CardDebuff.h"
#include "Monster.h"

using namespace std;

CardDebuff::CardDebuff(eObjectType objectType)
	: Card(objectType)
{
	mDebuffCardInfo = {};
}

CardDebuff::CardDebuff(const CardDebuff& other)
	: Card(other)
	, mDebuffCardInfo(other.mDebuffCardInfo)
{
}

CardDebuff::~CardDebuff()
{
}

void CardDebuff::Initialize()
{
}

Card* CardDebuff::Clone() const
{
	return new CardDebuff(*this);
}

void CardDebuff::Save(std::ofstream& fout)
{
	Card::Save(fout);

	fout.write((char*)&mDebuffCardInfo.DebuffType, sizeof(eDebuffFlag));
	fout.write((char*)&mDebuffCardInfo.DebuffCount, sizeof(int));

	int debuffNameSize = mDebuffCardInfo.DebuffName.size();

	fout.write((char*)&debuffNameSize, sizeof(int));
	fout.write(mDebuffCardInfo.DebuffName.c_str(), debuffNameSize);
}

void CardDebuff::Load(std::ifstream& fin)
{
	Card::Load(fin);

	fin.read((char*)&mDebuffCardInfo.DebuffType, sizeof(eDebuffFlag));
	fin.read((char*)&mDebuffCardInfo.DebuffCount, sizeof(int));

	int debuffNameSize = 0;
	fin.read((char*)&debuffNameSize, sizeof(int));

	constexpr int DEBUFF_NAME_SIZE = 16;
	char debuffName[DEBUFF_NAME_SIZE];

	fin.read(debuffName, debuffNameSize);
	debuffName[debuffNameSize] = '\0';
	mDebuffCardInfo.DebuffName = debuffName;
}

eCombatResult CardDebuff::ActivateCard(Player* player, Monster* monster) const
{
	monster->SetDebuffFlag(mDebuffCardInfo.DebuffType, mDebuffCardInfo.DebuffCount);
	
	cout << monster->GetName() << " got " << mDebuffCardInfo.DebuffName << endl;

	return eCombatResult::NONE;
}

