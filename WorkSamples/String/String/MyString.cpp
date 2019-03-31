#include "MyString.h"

namespace assignment1
{
	MyString::MyString(const char* s)
		: mSize(strlen(s))
		, mCapacity(INIT_CAPACITY)
		, mString(new char[mCapacity + 1])
	{
		if (mSize > mCapacity)
		{
			setNewCapacity(mSize);
		}

		memcpy(mString, s, mSize + 1);
	}

	MyString::MyString(const MyString& other)
		: mSize(other.mSize)
		, mCapacity(other.mCapacity)
		, mString(new char[mCapacity + 1])
	{
		memcpy(mString, other.mString, mSize + 1);
	}

	MyString::~MyString()
	{
		delete[] mString;
	}

	unsigned int MyString::GetLength() const
	{
		return mSize;
	}

	const char* MyString::GetCString() const
	{
		return mString;
	}

	void MyString::Append(const char* s)
	{
		size_t newSize = mSize + strlen(s);

		if (newSize > mCapacity)
		{
			setNewCapacity(newSize);

			char* newString = new char[mCapacity + 1];
			memcpy(newString, mString, mSize + 1);

			delete[] mString;
			mString = newString;

		}

		memcpy(mString + mSize, s, strlen(s) + 1);
		mSize = newSize;
	}

	MyString MyString::operator+(const MyString& other) const
	{
		MyString result(mString);

		result.Append(other.mString);

		return result;
	}

	int MyString::IndexOf(const char* s)
	{
		return handleIndexOf(s, FIRST);
	}

	int MyString::LastIndexOf(const char* s)
	{
		return handleIndexOf(s, LAST);
	}

	int MyString::handleIndexOf(const char* s, int firstOrLast) const
	{
		if (s[0] == '\0')
		{
			if (firstOrLast == FIRST)
			{
				return 0;
			}
			else if (firstOrLast == LAST)
			{
				return mSize;
			}
		}

		int index = -1;

		for (size_t i = 0; i < mSize; i++)
		{
			bool bIsContained = true;

			for (size_t j = 0; j < strlen(s); j++)
			{
				if (mString[i + j] != s[j])
				{
					bIsContained = false;
					break;
				}
			}

			if (bIsContained == true)
			{
				index = i;

				if (firstOrLast == FIRST)
				{
					break;
				}
				else if (firstOrLast == LAST)
				{
					bIsContained = false;
				}
			}
		}

		return index;
	}

	void MyString::Interleave(const char* s)
	{
		mSize += strlen(s);

		if (mSize > mCapacity)
		{
			setNewCapacity(mSize);

			char* newString = new char[mCapacity + 1];

			handleInterleave(newString, s, mSize);

			delete[] mString;
			mString = newString;
		}
		else
		{
			char newString[INIT_CAPACITY + 1];

			handleInterleave(newString, s, mSize);

			memcpy(mString, newString, mSize + 1);
		}
	}

	void MyString::handleInterleave(char* newString, const char* s, size_t size) const
	{
		size_t countFirstStrLen = 0;
		size_t countSecondStrLen = 0;

		for (size_t i = 0; i < mSize;)
		{
			if (countFirstStrLen < strlen(mString))
			{
				newString[i] = mString[countFirstStrLen];
				i++;
				countFirstStrLen++;
			}

			if (countSecondStrLen < strlen(s))
			{
				newString[i] = s[countSecondStrLen];
				i++;
				countSecondStrLen++;
			}
		}
		newString[mSize] = '\0';
	}

	bool MyString::RemoveAt(unsigned int index)
	{
		if (index >= mSize)
		{
			return false;
		}

		for (size_t i = index; i < mSize; i++)
		{
			mString[i] = mString[i + 1];
		}

		mSize--;
		return true;
	}

	void MyString::PadLeft(unsigned int totalLength)
	{
		handlePadLeftRight(totalLength, LEFT, ' ');
	}

	void MyString::PadLeft(unsigned int totalLength, const char c)
	{
		handlePadLeftRight(totalLength, LEFT, c);
	}

	void MyString::PadRight(unsigned int totalLength)
	{
		handlePadLeftRight(totalLength, RIGHT, ' ');
	}

	void MyString::PadRight(unsigned int totalLength, const char c)
	{
		handlePadLeftRight(totalLength, RIGHT, c);
	}

	void MyString::handlePadLeftRight(unsigned int totalLength, int leftOrRight, const char c)
	{
		if (totalLength <= mSize)
		{
			return;
		}

		size_t newSize = totalLength;
		size_t numberOfPads = totalLength - mSize;

		if (newSize > mCapacity)
		{
			setNewCapacity(newSize);

			char* newString = new char[mCapacity + 1];

			if (leftOrRight == LEFT)
			{
				memset(newString, c, numberOfPads);
				memcpy(newString + numberOfPads, mString, mSize);
			}

			if (leftOrRight == RIGHT)
			{
				memcpy(newString, mString, mSize);
				memset(newString + mSize, c, numberOfPads);
			}

			newString[newSize] = '\0';
			delete[] mString;
			mString = newString;
		}
		else
		{
			char newString[INIT_CAPACITY + 1];

			if (leftOrRight == LEFT)
			{
				memset(newString, c, numberOfPads);
				memcpy(newString + numberOfPads, mString, mSize + 1);
				memcpy(mString, newString, newSize + 1);
			}
			else if (leftOrRight == RIGHT)
			{
				memset(mString + mSize, c, numberOfPads);
				mString[newSize] = '\0';
			}
		}
		mSize = newSize;
	}

	void MyString::Reverse()
	{
		char* p = mString;
		char* q = mString + mSize - 1;

		while (p < q)
		{
			char temp = *p;
			*p = *q;
			*q = temp;

			p++;
			q--;
		}
	}

	bool MyString::operator==(const MyString& rhs) const
	{
		for (size_t i = 0; i <= mSize; i++)
		{
			if (mString[i] != rhs.mString[i])
			{
				return false;
			}
		}

		return true;
	}

	void MyString::ToLower()
	{
		for (size_t i = 0; i < mSize; i++)
		{
			if (mString[i] >= 'A' && mString[i] <= 'Z')
			{
				mString[i] += 32;
			}
		}
	}

	void MyString::ToUpper()
	{
		for (size_t i = 0; i < mSize; i++)
		{
			if (mString[i] >= 'a' && mString[i] <= 'z')
			{
				mString[i] -= 32;
			}
		}
	}

	size_t MyString::strlen(const char* s) const
	{
		size_t length = 0;

		while (s[length] != '\0')
		{
			length++;
		}

		return length;
	}

	void MyString::memcpy(void* dest, const void* src, size_t size)
	{
		char* cDest = (char*)dest;
		char* cSrc = (char*)src;

		for (size_t i = 0; i < size; i++)
		{
			cDest[i] = cSrc[i];
		}
	}

	void MyString::memset(void* dest, int ch, size_t size)
	{
		char* cDest = (char*)dest;

		for (size_t i = 0; i < size; i++)
		{
			cDest[i] = (char)ch;
		}
	}

	void MyString::setNewCapacity(const size_t size)
	{
		while (size > mCapacity)
		{
			mCapacity = (mCapacity + 1) * 2 - 1;
		}
	}
}