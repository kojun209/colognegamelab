#pragma once
namespace assignment1
{
	class MyString
	{
	public:
		MyString(const char* s);
		MyString(const MyString& other);
		~MyString();

		unsigned int GetLength() const;
		const char* GetCString() const;
		void Append(const char* s);
		MyString operator+(const MyString& other) const;
		int IndexOf(const char* s);
		int LastIndexOf(const char* s);
		void Interleave(const char* s);
		bool RemoveAt(unsigned int i);
		void PadLeft(unsigned int totalLength);
		void PadLeft(unsigned int totalLength, const char c);
		void PadRight(unsigned int totalLength);
		void PadRight(unsigned int totalLength, const char c);
		void Reverse();
		bool operator==(const MyString& rhs) const;
		void ToLower();
		void ToUpper();

	private:
		enum { INIT_CAPACITY = 15, LEFT = 0, RIGHT = 1, FIRST = 2, LAST = 3 };
		size_t mSize;
		size_t mCapacity;
		char* mString;

		size_t strlen(const char* s) const;
		void memcpy(void* dest, const void* src, size_t size);
		void memset(void* dest, int ch, size_t size);
		void setNewCapacity(size_t size);
		void handleInterleave(char* newString, const char* s, size_t size) const;
		void handlePadLeftRight(unsigned int totalLength, int leftOrRight, const char c);
		int handleIndexOf(const char* s, int firstOrLast) const;
	};
}