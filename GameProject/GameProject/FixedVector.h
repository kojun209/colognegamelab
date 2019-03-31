#pragma once
template<typename T, size_t N>
class FixedVector
{
public:
	FixedVector();

	bool Add(const T& t);
	bool Remove(const T& t);
	bool RemoveByIndex(unsigned int index);
	bool RemoveLast();
	const T& Get(unsigned int index) const;
	const T& GetLast() const;
	T& operator[](unsigned int index);
	int GetIndex(const T& t) const;
	size_t GetSize() const;
	size_t GetCapacity() const;
	bool IsEmpty() const;
	void Clear();

private:
	size_t mSize;
	T mArray[N];
};

template<typename T, size_t N>
inline FixedVector<T, N>::FixedVector()
	: mSize(0)
{
	memset(mArray, 0, sizeof(T) * N);
}

template<typename T, size_t N>
inline bool FixedVector<T, N>::Add(const T& t)
{
	if (mSize >= N)
	{
		return false;
	}

	mArray[mSize++] = t;
	return true;
}

template<typename T, size_t N>
inline bool FixedVector<T, N>::Remove(const T& t)
{
	for (size_t i = 0; i < mSize; i++)
	{
		if (mArray[i] == t)
		{
			for (size_t j = i; j < mSize; j++)
			{
				mArray[j] = mArray[j + 1];
			}

			mSize--;
			return true;
		}
	}

	return false;
}

template<typename T, size_t N>
inline bool FixedVector<T, N>::RemoveByIndex(unsigned int index)
{
	for (size_t i = index; i < mSize; i++)
	{
		for (size_t j = i; j < mSize; j++)
		{
			mArray[j] = mArray[j + 1];
		}

		mSize--;
		return true;
	}

	return false;
}

template<typename T, size_t N>
inline bool FixedVector<T, N>::RemoveLast()
{
	if (IsEmpty())
	{
		return false;
	}

	mArray[mSize - 1] = 0;
	mSize--;

	return true;
}

template<typename T, size_t N>
inline const T& FixedVector<T, N>::Get(unsigned int index) const
{
	return mArray[index];
}

template<typename T, size_t N>
inline const T& FixedVector<T, N>::GetLast() const
{
	return mArray[mSize - 1];
}

template<typename T, size_t N>
inline T& FixedVector<T, N>::operator[](unsigned int index)
{
	return mArray[index];
}

template<typename T, size_t N>
inline int FixedVector<T, N>::GetIndex(const T& t) const
{
	for (size_t i = 0; i < mSize; i++)
	{
		if (mArray[i] == t)
		{
			return i;
		}
	}

	return -1;
}

template<typename T, size_t N>
inline size_t FixedVector<T, N>::GetSize() const
{
	return mSize;
}

template<typename T, size_t N>
inline size_t FixedVector<T, N>::GetCapacity() const
{
	return N;
}

template<typename T, size_t N>
inline bool FixedVector<T, N>::IsEmpty() const
{
	return mSize == 0;
}

template<typename T, size_t N>
inline void FixedVector<T, N>::Clear()
{
	memset(mArray, 0, sizeof(T) * mSize);
	mSize = 0;
}
