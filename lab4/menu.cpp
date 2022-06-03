#include <iostream>

#include "branch.hpp"
#include "tree.hpp"
#include "error.h"

using namespace std;

int FuncMap(int a)
{
    return 2 * a;
}

bool FuncWhere(int a)
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

int FuncReduce(int a, int b)
{
    return a + b;
}

int GetInt(Error* error)
{
    char buf[256];
    fgets(buf, sizeof(buf), stdin);
    int sc;
    if (sscanf_s(buf, "%d", &sc) != 1)
    {
        *error = WRONGINPUTINT;
    }
    return sc;
}

void FuncError(Error error)
{
    switch (error)
    {
    case 1:
        printf("������. ������� ������������� �����\n");
        break;
    }
}

int CheckInt()
{
    int sc;
    Error error;
    do
    {
        error = NOT;
        sc = GetInt(&error);
        FuncError(error);
    } while (error == WRONGINPUTINT);
    return sc;
}

void FuncMenu()
{
	setlocale(LC_CTYPE, "Russian");

    system("cls");
    cout << "������� ������" << endl;
    int size;
    size = CheckInt();
    Tree<int>* tree = new Tree<int>();
    int data;
    for (int i = 1; i <= size; i++)
    {
        cout << "������� " << i << " ��������" << endl;
        data = CheckInt();
        tree->Add(data);
    }
   
    int menu = 0;
    while (menu != 8)
    {
        system("cls");
        cout << "------------��������------------" << endl;
        cout << "1. �������� ��� �������� �� 2" << endl;
        cout << "2. ������ ��� �������� ��������" << endl;
        cout << "3. ������� ����� ���� ��������" << endl;
        cout << "4. ������� �������� ������" << endl;
        cout << "5. ������� �������� ���������" << endl;
        cout << "6. ������� ������" << endl;
        cout << "7. �������� �������" << endl;
        cout << "8. �����" << endl;
        cout << "--------------------------------" << endl;

        cout << "������� ����� ������" << endl;
        menu = CheckInt();
        switch (menu)
        {
        case 1:
        {
            system("cls");
            int (*FM)(int) = &FuncMap;
            tree = tree->Map(FM);
            cout << "������" << endl;
            system("pause");
            break;
        }

        case 2:
        {
            system("cls");
            bool (*FW)(int) = &FuncWhere;
            tree = tree->Where(FW);
            cout << "������" << endl;
            system("pause");
            break;
        }

        case 3:
        {
            system("cls");
            int (*FR)(int, int) = &FuncReduce;
            int t = tree->Reduce(FR, 0);
            cout << t << endl;
            system("pause");
            break;
        }

        case 4:
            system("cls");
            tree->Print();
            system("pause");
            break;
 
        case 5:
        {
            system("cls");
            Branch<int>* branch;
            int wh = 1;
            while (wh == 1)
            {
                cout << "������� ��������" << endl;
                int data;
                data = CheckInt();
                branch = tree->Search(data);
                if (branch != nullptr)
                {
                    wh = 0;
                }
                else
                {
                    cout << "������ �������� � ������ ���" << endl << endl;
                }
            }
            Tree<int>* subtree = tree->GetSubtree(branch);
            subtree->Print();
            system("pause");
            break;
        }

        case 6:
            system("cls");
            cout << tree->GetSize() << endl;
            system("pause");
            break;

        case 7:
            system("cls");
            cout << "������� " << tree->GetSize() + 1 << " ��������" << endl;
            data = CheckInt();
            tree->Add(data);
            break;

        case 8:
            system("cls");
            cout << "����� ������ ���������" << endl;
            break;

        default:
            cout << "������ ������ ���" << endl;
        }
    }
}