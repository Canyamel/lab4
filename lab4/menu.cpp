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
        printf("Ошибка. Введите целочисленное число\n");
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
    cout << "Введите размер" << endl;
    int size;
    size = CheckInt();
    Tree<int>* tree = new Tree<int>();
    int data;
    for (int i = 1; i <= size; i++)
    {
        cout << "Введите " << i << " значение" << endl;
        data = CheckInt();
        tree->Add(data);
    }
   
    int menu = 0;
    while (menu != 8)
    {
        system("cls");
        cout << "------------Терминал------------" << endl;
        cout << "1. Умножить все значения на 2" << endl;
        cout << "2. Убрать все нечётные значения" << endl;
        cout << "3. Вывести сумму всех значений" << endl;
        cout << "4. Вывести значения дерева" << endl;
        cout << "5. Вывести значения поддерева" << endl;
        cout << "6. Вывести размер" << endl;
        cout << "7. Добавить элемент" << endl;
        cout << "8. Выход" << endl;
        cout << "--------------------------------" << endl;

        cout << "Введите номер пункта" << endl;
        menu = CheckInt();
        switch (menu)
        {
        case 1:
        {
            system("cls");
            int (*FM)(int) = &FuncMap;
            tree = tree->Map(FM);
            cout << "Готово" << endl;
            system("pause");
            break;
        }

        case 2:
        {
            system("cls");
            bool (*FW)(int) = &FuncWhere;
            tree = tree->Where(FW);
            cout << "Готово" << endl;
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
                cout << "Введите значение" << endl;
                int data;
                data = CheckInt();
                branch = tree->Search(data);
                if (branch != nullptr)
                {
                    wh = 0;
                }
                else
                {
                    cout << "Такого значения в дереве нет" << endl << endl;
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
            cout << "Введите " << tree->GetSize() + 1 << " значение" << endl;
            data = CheckInt();
            tree->Add(data);
            break;

        case 8:
            system("cls");
            cout << "Конец работы программы" << endl;
            break;

        default:
            cout << "Такого пункта нет" << endl;
        }
    }
}