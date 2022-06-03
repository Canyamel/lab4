#pragma once

#include "branch.hpp"
#include "tree.hpp"

#include <iostream>
#include <cassert>

using namespace std;

void Test_Tree_GetSize()
{
	Tree<int>* test = new Tree<int>();

	test->Add(5);
	test->Add(6);
	test->Add(1);
	test->Add(7);
	test->Add(4);

	assert(test->GetSize() == 5);

	//cout << "Test_Tree_GetSize OK" << endl;
}

//----------------

void Test_Tree_Search()
{
	Tree<int>* test = new Tree<int>();

	test->Add(5);
	test->Add(6);
	test->Add(1);
	test->Add(7);
	test->Add(4);

	Branch<int>* t = test->Search(4);
	assert(t->data == 4);
	t = test->Search(5);
	assert(t->data == 5);
	t = test->Search(1);
	assert(t->data == 1);
	t = test->Search(7);
	assert(t->data == 7);
	t = test->Search(6);
	assert(t->data == 6);
	t = test->Search(9);
	assert(t == nullptr);

	//cout << "Test_Tree_Search OK" << endl;
}

//----------------

void Test_Tree_Destroy()
{
	Tree<int>* test = new Tree<int>();

	test->Add(5);
	test->Add(6);
	test->Add(1);
	test->Add(7);
	test->Add(4);

	test->Destroy();

	Branch<int>* t = test->GetRoot();

	assert(t == nullptr);
	assert(test->GetSize() == 0);

	//cout << "Test_Tree_Destroy OK" << endl;
}

//----------------

int FuncTestMap(int a)
{
	return 2 * a;
}

void Test_Tree_Map()
{
	Tree<int>* test = new Tree<int>();

	test->Add(5);
	test->Add(6);
	test->Add(1);
	test->Add(7);
	test->Add(4);

	int (*TestF)(int) = &FuncTestMap;

	test = test->Map(TestF);

	Branch<int>* t = test->Search(8);
	assert(t->data == 8);
	t = test->Search(10);
	assert(t->data == 10);
	t = test->Search(2);
	assert(t->data == 2);
	t = test->Search(14);
	assert(t->data == 14);
	t = test->Search(12);
	assert(t->data == 12);

	//cout << "Test_Tree_Map OK" << endl;
}

//----------------

bool FuncTestWhere(int a)
{
	if (a % 2 == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void Test_Tree_Where()
{
	Tree<int>* test = new Tree<int>();

	test->Add(5);
	test->Add(6);
	test->Add(1);
	test->Add(7);
	test->Add(4);

	bool (*TestF)(int) = &FuncTestWhere;

	test = test->Where(TestF);

	Branch<int>* t = test->Search(4);
	assert(t->data == 4);

	t = test->Search(6);
	assert(t->data == 6);
	t = test->Search(5);
	assert(t == nullptr);
	t = test->Search(1);
	assert(t == nullptr);
	t = test->Search(7);
	assert(t == nullptr);

	//cout << "Test_Tree_Where OK" << endl;
}

//----------------

int FuncTestReduce(int a, int b)
{
	return 2*a + b;
}

void Test_Tree_Reduce()
{
	Tree<int>* test = new Tree<int>();

	test->Add(1);
	test->Add(2);
	test->Add(3);

	int (*TestF)(int, int) = &FuncTestReduce;

	int t = test->Reduce(TestF, 0);

	assert(t == 12);

	//cout << "Test_Tree_Reduce OK" << endl;
}

//----------------

void Test_Tree_GetSubtree()
{
	Tree<int>* test1 = new Tree<int>();

	test1->Add(5);
	test1->Add(6);
	test1->Add(3);
	test1->Add(4);
	test1->Add(2);
	test1->Add(1);

	Branch<int>* t = test1->Search(3);

	Tree<int>* test2 = new Tree<int>();

	test2 = test1->GetSubtree(t);

	t = test2->Search(3);
	assert(t->data == 3);
	t = test2->Search(4);
	assert(t->data == 4);
	t = test2->Search(2);
	assert(t->data == 2);
	t = test2->Search(2);
	assert(t->data == 2);
	t = test2->Search(5);
	assert(t == nullptr);
	t = test2->Search(6);
	assert(t == nullptr);

	//cout << "Test_Tree_GetSubtree OK" << endl;
}

//----------------------------------------------//

void UnitTest_Tree()
{
	Test_Tree_GetSize();
	Test_Tree_Search();
	Test_Tree_Destroy();
	Test_Tree_Map();
	Test_Tree_Where();
	Test_Tree_Reduce();
	Test_Tree_GetSubtree();
}