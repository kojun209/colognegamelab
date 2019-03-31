#pragma once

#include <string>

#include "EObjectType.h"

class Object
{
	friend class ObjectManager;

public:
	virtual void Initialize() = 0;
	virtual void Render() const = 0;
	virtual Object* Clone() const = 0;
	virtual void Save(std::ofstream& fout);
	virtual void Load(std::ifstream& fin);

	inline void SetName(const char* objectName);
	inline std::string GetName() const;
	inline eObjectType GetObjectType() const;

protected:
	Object(eObjectType objectType);
	Object(const Object& other);
	virtual ~Object() = 0;

protected:
	std::string mObjectName;
	eObjectType mObjectType;
};

void Object::SetName(const char* objectName)
{
	mObjectName = objectName;
}

inline std::string Object::GetName() const
{
	return mObjectName;
}

inline eObjectType Object::GetObjectType() const
{
	return mObjectType;
}