#include <fstream>

#include "Object.h"

Object::Object(eObjectType objectType)
	: mObjectType(objectType)
{
}

Object::Object(const Object& other)
	: mObjectName(other.mObjectName)
	, mObjectType(other.mObjectType)
{
}

Object::~Object()
{
}

void Object::Save(std::ofstream& fout)
{
	fout.write((char*)&mObjectType, sizeof(eObjectType));

	int objectNameSize = mObjectName.size();

	fout.write((char*)&objectNameSize, sizeof(int));
	fout.write(mObjectName.c_str(), objectNameSize);
}

void Object::Load(std::ifstream& fin)
{
	fin.read((char*)&mObjectType, sizeof(eObjectType));

	int objectNameSize = 0;
	fin.read((char*)&objectNameSize, sizeof(int));
	
	constexpr int NAME_SIZE = 32;
	char objectName[NAME_SIZE];
	
	fin.read(objectName, objectNameSize);
	objectName[objectNameSize] = '\0';
	mObjectName = objectName;
}