#pragma once

#include <memory>
#include <vector>

namespace assignment4
{
	template<typename T>
	class TreeNode;

	template<typename T>
	class BinarySearchTree final
	{
	public:
		void Insert(std::unique_ptr<T> data);
		bool Search(const T& data);
		bool Delete(const T& data);
		const std::weak_ptr<TreeNode<T>> GetRootNode() const;

		static std::vector<T> TraverseInOrder(const std::shared_ptr<TreeNode<T>> startNode);

	private:
		static void traverseInOrderRecursive(const std::shared_ptr<TreeNode<T>> startNode, std::vector<T>& v);

	private:
		std::shared_ptr<TreeNode<T>> mRoot;
	};

	template<typename T>
	void BinarySearchTree<T>::Insert(std::unique_ptr<T> data)
	{
		std::shared_ptr<TreeNode<T>> node = mRoot;
		std::shared_ptr<TreeNode<T>> parent = nullptr;

		while (node != nullptr)
		{
			parent = node;

			if (*data <= *node->Data)
			{
				node = node->Left;
			}
			else
			{
				node = node->Right;
			}
		}

		std::shared_ptr<TreeNode<T>> newNode = std::make_shared<TreeNode<T>>(parent, std::move(data));

		if (mRoot == nullptr)
		{
			mRoot = newNode;

			return;
		}

		if (*newNode->Data <= *parent->Data)
		{
			parent->Left = newNode;
		}
		else
		{
			parent->Right = newNode;
		}
	}

	template<typename T>
	const std::weak_ptr<TreeNode<T>> BinarySearchTree<T>::GetRootNode() const
	{
		return mRoot;
	}

	template<typename T>
	bool BinarySearchTree<T>::Search(const T& data)
	{
		std::shared_ptr<TreeNode<T>> node = mRoot;

		while (node != nullptr)
		{
			if (data == *node->Data)
			{
				return true;
			}

			if (data < *node->Data)
			{
				node = node->Left;
			}
			else
			{
				node = node->Right;
			}
		}

		return false;
	}

	template<typename T>
	bool BinarySearchTree<T>::Delete(const T& data)
	{
		std::shared_ptr<TreeNode<T>> node = mRoot;
		bool bNotFound = true;

		while (node != nullptr)
		{
			if (data == *node->Data)
			{
				bNotFound = false;
				break;
			}

			if (data < *node->Data)
			{
				node = node->Left;
			}
			else
			{
				node = node->Right;
			}
		}

		if (bNotFound)
		{
			return false;
		}

		std::shared_ptr<TreeNode<T>> nodeToDelete;
		std::shared_ptr<TreeNode<T>> successor;

		if (node->Left == nullptr || node->Right == nullptr)
		{
			nodeToDelete = node;
		}
		else
		{
			successor = node->Right;

			while (successor->Left != nullptr)
			{
				successor = successor->Left;
			}

			nodeToDelete = successor;
		}

		std::shared_ptr<TreeNode<T>> child;

		if (nodeToDelete->Left != nullptr)
		{
			child = nodeToDelete->Left;
		}
		else
		{
			child = nodeToDelete->Right;
		}

		if (child != nullptr)
		{
			child->Parent = nodeToDelete->Parent;
		}

		if (nodeToDelete->Parent.lock() == nullptr)
		{
			mRoot = child;
		}
		else if (nodeToDelete == nodeToDelete->Parent.lock()->Left)
		{
			nodeToDelete->Parent.lock()->Left = child;
		}
		else
		{
			nodeToDelete->Parent.lock()->Right = child;
		}

		if (node != nodeToDelete)
		{
			*node->Data = *nodeToDelete->Data;
		}

		return true;
	}

	template<typename T>
	std::vector<T> BinarySearchTree<T>::TraverseInOrder(const std::shared_ptr<TreeNode<T>> startNode)
	{
		std::vector<T> v;

		traverseInOrderRecursive(startNode, v);

		return v;
	}

	template<typename T>
	inline void BinarySearchTree<T>::traverseInOrderRecursive(const std::shared_ptr<TreeNode<T>> startNode, std::vector<T>& v)
	{
		if (startNode != nullptr)
		{
			traverseInOrderRecursive(startNode->Left, v);
			v.push_back(*startNode->Data);
			traverseInOrderRecursive(startNode->Right, v);
		}
	}
}