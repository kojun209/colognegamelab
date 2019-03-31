#include <iostream>
#include <fstream>

#include "CardBuff.h"
#include "Player.h"

using namespace std;

CardBuff::CardBuff(eObjectType objectType)
	: Card(objectType)
{
	mBuffCardInfo = {};
}

CardBuff::CardBuff(const CardBuff& other)
	: Card(other)
	, mBuffCardInfo(other.mBuffCardInfo)
{
}

CardBuff::~CardBuff()
{
}

void CardBuff::Initialize()
{
}

Card* CardBuff::Clone() const
{
	return new CardBuff(*this);
}

void CardBuff::Save(std::ofstream& fout)
{
	Card::Save(fout);

	fout.write((char*)&mBuffCardInfo.BuffType, sizeof(eBuffFlag));
	fout.write((char*)&mBuffCardInfo.BuffCount, sizeof(int));

	int buffNameSize = mBuffCardInfo.BuffName.size();

	fout.write((char*)&buffNameSize, sizeof(int));
	fout.write(mBuffCardInfo.BuffName.c_str(), buffNameSize);
}

void CardBuff::Load(std::ifstream& fin)
{
	Card::Load(fin);

	fin.read((char*)&mBuffCardInfo.BuffType, sizeof(eBuffFlag));
	fin.read((char*)&mBuffCardInfo.BuffCount, sizeof(int));

	int buffNameSize = 0;
	fin.read((char*)&buffNameSize, sizeof(int));

	constexpr int BUFF_NAME_SIZE = 16;
	char buffName[BUFF_NAME_SIZE];

	fin.read(buffName, buffNameSize);
	buffName[buffNameSize] = '\0';
	mBuffCardInfo.BuffName = buffName;
}

eCombatResult CardBuff::ActivateCard(Player* player, Monster* monster) const
{
	player->SetBuffFlag(mBuffCardInfo.BuffType, mBuffCardInfo.BuffCount);

	cout << player->GetName() << " got " << mBuffCardInfo.BuffName
		<< " for " << mBuffCardInfo.BuffCount << " turns" << endl;

	return eCombatResult::NONE;
}

