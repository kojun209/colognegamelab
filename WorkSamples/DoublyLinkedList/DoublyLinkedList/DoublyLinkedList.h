#pragma once

#include <memory>

namespace lab10
{
	template<typename T>
	class Node;

	template<typename T>
	class DoublyLinkedList
	{
	public:
		DoublyLinkedList();
		void Insert(std::unique_ptr<T> data);
		void Insert(std::unique_ptr<T> data, unsigned int index);
		bool Delete(const T& data);
		bool Search(const T& data) const;

		std::shared_ptr<Node<T>> operator[](unsigned int index) const;
		unsigned int GetLength() const;

	private:
		unsigned int mLength;
		std::shared_ptr<Node<T>> mHead;
	};

	template<typename T> DoublyLinkedList<T>::DoublyLinkedList()
		: mLength(0)
	{
	}

	template<typename T>
	void DoublyLinkedList<T>::Insert(std::unique_ptr<T> data)
	{
		std::shared_ptr<Node<T>> newNode = std::make_shared<Node<T>>(std::move(data));

		if (mLength == 0)
		{
			mHead = newNode;
		}
		else
		{
			(*this)[mLength - 1]->Next = newNode;
			newNode->Previous = (*this)[mLength - 1];
		}

		mLength++;
	}

	template<typename T>
	void DoublyLinkedList<T>::Insert(std::unique_ptr<T> data, unsigned int index)
	{
		if (mLength == 0 || index >= mLength)
		{
			Insert(std::move(data));

			return;
		}

		std::shared_ptr<Node<T>> newNode = std::make_shared<Node<T>>(std::move(data));

		if (index == 0)
		{
			newNode->Next = mHead;
			mHead->Previous = newNode;
			mHead = newNode;
		}
		else
		{
			std::shared_ptr<Node<T>> node = mHead;

			for (size_t i = 0; i < index - 1; i++)
			{
				node = node->Next;
			}

			newNode->Next = node->Next;
			newNode->Previous = node;
			node->Next = newNode;
			newNode->Next->Previous = newNode;
		}

		mLength++;
	}

	template<typename T>
	bool DoublyLinkedList<T>::Delete(const T& data)
	{
		if (mLength == 0)
		{
			return false;
		}

		std::shared_ptr<Node<T>> node = mHead;

		while (node != nullptr)
		{
			if (*node->Data == data)
			{
				break;
			}

			node = node->Next;
		}

		if (node == nullptr)
		{
			return false;
		}

		if (mLength == 1)
		{
			mHead = nullptr;
		}
		else if (node == mHead)
		{
			mHead = mHead->Next;
		}
		else if (node == (*this)[mLength - 1])
		{
			node = node->Previous.lock();
			node->Next = nullptr;
		}
		else
		{
			node->Previous.lock()->Next = node->Next;
			node->Next->Previous = node->Previous;
		}

		mLength--;

		return true;
	}

	template<typename T>
	bool DoublyLinkedList<T>::Search(const T& data) const
	{
		if (mLength == 0)
		{
			return false;
		}

		std::shared_ptr<Node<T>> node = mHead;

		while (node != nullptr)
		{
			if (*node->Data == data)
			{
				return true;
			}

			node = node->Next;
		}

		return false;
	}

	template<typename T>
	std::shared_ptr<Node<T>> DoublyLinkedList<T>::operator[](unsigned int index) const
	{
		if (index >= mLength)
		{
			return nullptr;
		}

		std::shared_ptr<Node<T>> node = mHead;

		for (size_t i = 0; i < index; i++)
		{
			node = node->Next;
		}

		return node;
	}

	template<typename T>
	unsigned int DoublyLinkedList<T>::GetLength() const
	{
		return mLength;
	}
}