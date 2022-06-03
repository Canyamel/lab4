#pragma once

#include "branch.hpp"

#include <iostream>

using namespace std;

template <class T>
class Tree
{
private:
	Branch<T>* root; //Указатель на корень дерева
	int size; //Кол-во элементов в дереве
	
public:
	Tree();
	Tree(T);
	Tree(Branch<T>*);
	~Tree();
	void Add(T, Branch<T>*);
	void Add(T);
	int GetSize();
	Branch<T>* GetRoot();
	void Print(Branch<T>*);
	void Print();
	Branch<T>* Search(T, Branch<T>*);
	Branch<T>* Search(T);
	void Destroy(Branch<T>*);
	void Destroy();
	void AddArray(Branch<T>*, T*, int*);
	T* GetArray();
	T* GetArray(Branch<T>*, int*);
	void DeleteBranch(T);
	Tree<T>* Map(T(*Func)(T));
	Tree<T>* Where(bool (*Func)(T));
	T Reduce(T(*Func)(T, T), T);
	Tree<T>* GetSubtree(Branch<T>*);
};

template <class T>
Tree<T>::Tree() : root(nullptr), size(0) {}

template <class T>
Tree<T>::Tree(T aData) : size(1)
{
	root = new Branch<T>(aData);
}

template <class T>
Tree<T>::Tree(Branch<T>* aBranch) : root(aBranch), size(1) {}

template <class T>
Tree<T>::~Tree()
{
	Destroy();
}

template <class T>
void Tree<T>::Add(T aData, Branch<T>* aBranch)
{

	if (aBranch->data > aData)
	{
		if (aBranch->left)
		{
			Add(aData, aBranch->left);
		}
		else
		{
			aBranch->left = new Branch<T>(aData);
			size++;
		}
	}
	else
	{
		if (aBranch->right)
		{
			Add(aData, aBranch->right);
		}
		else
		{
			aBranch->right = new Branch<T>(aData);
			size++;
		}
	}
}

template <class T>
void Tree<T>::Add(T aData)
{
	if (root)
	{
		Add(aData, root);
	}
	else
	{
		root = new Branch<T>(aData);
		size++;
	}
}

template <class T>
int Tree<T>::GetSize()
{
	return size;
}

template <class T>
Branch<T>* Tree<T>::GetRoot()
{
	return root;
}

template <class T>
void Tree<T>::Print(Branch<T>* aBranch)
{
	if (aBranch)
	{
		Print(aBranch->left);
		cout << aBranch->data << " ";
		Print(aBranch->right);
	}
}

template <class T>
void Tree<T>::Print()
{
	Print(root);
	cout << endl;
}

template <class T>
Branch<T>* Tree<T>::Search(T aData, Branch<T>* aBranch)
{
	if (aBranch)
	{
		if (aData == aBranch->data)
		{
			return aBranch;
		}
		if (aBranch->data > aData)
		{
			return Search(aData, aBranch->left);
		}
		else
		{
			return Search(aData, aBranch->right);
		}
	}
	else
	{
		return nullptr;
	}
}

template <class T>
Branch<T>* Tree<T>::Search(T aData)
{
	if (root)
	{
		return Search(aData, root);
	}
}

template <class T>
void Tree<T>::Destroy(Branch<T>* aBranch)
{
	if (aBranch)
	{
		Destroy(aBranch->left);
		Destroy(aBranch->right);
		delete aBranch;
	}
	size = 0;
}

template <class T>
void Tree<T>::Destroy()
{
	Destroy(root);
	root = nullptr;
}

template <class T>
void Tree<T>::AddArray(Branch<T>* aBranch, T* array, int* i)
{
	if (aBranch)
	{
		int j = *i;
		array[j] = aBranch->data;
		*i = j + 1;
		AddArray(aBranch->left, array, i);
		AddArray(aBranch->right, array, i);
	}
}

template <class T>
T* Tree<T>::GetArray()
{
	int i = 0;
	T* array = new T[size];
	AddArray(root, array, &i);
	return array;
}

template <class T>
T* Tree<T>::GetArray(Branch<T>* aBranch, int* i)
{
	T* array = new T[size];
	AddArray(aBranch, array, i);
	return array;
}

template <class T>
Tree<T>* Tree<T>::Map(T(*Func)(T))
{
	Tree<T>* newTree = new Tree<T>();
	T* array = this->GetArray();
	for (int i = 0; i < size; i++)
	{
		newTree->Add(Func(array[i]));
	}
	return newTree;
}

template <class T>
Tree<T>* Tree<T>::Where(bool (*Func)(T))
{
	Tree<T>* newTree = new Tree<T>();
	T* array = this->GetArray();
	for (int i = 0; i < size; i++)
	{
		if (Func(array[i]))
		{
			newTree->Add(array[i]);
		}
	}
	return newTree;
}

template <class T>
T Tree<T>::Reduce(T(*Func)(T, T), T sc)
{
	T* array = this->GetArray();
	for (int i = 0; i < size; i++)
	{
		sc = Func(array[i], sc);
	}
	return sc;
}

template <class T>
Tree<T>* Tree<T>::GetSubtree(Branch<T>* aBranch)
{
	int i = 0;
	Tree<T>* newTree = new Tree<T>();
	T* array = GetArray(aBranch, &i);
	for (int j = 0; j < i; j++)
	{
		newTree->Add(array[j]);
	}
	return newTree;
}