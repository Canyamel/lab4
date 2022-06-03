#pragma once

template <class T>
class Branch
{
public:
	T data; //Поле ветки
	Branch* left; //Указатель на левую ветку
	Branch* right; //Указатель на правую ветку

	Branch(T);
};

template <class T>
Branch<T>::Branch(T aData) : data(aData), left(nullptr), right(nullptr) {}