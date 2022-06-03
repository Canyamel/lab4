#pragma once

template <class T>
class Branch
{
public:
	T data; //���� �����
	Branch* left; //��������� �� ����� �����
	Branch* right; //��������� �� ������ �����

	Branch(T);
};

template <class T>
Branch<T>::Branch(T aData) : data(aData), left(nullptr), right(nullptr) {}