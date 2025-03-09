#include "Header.h"
using namespace std;

int main()
{
    int choice = -1, i = 0, j = 0, elem, input = -1;
    Double_Arr first_arr(0, 0);
    Double_Arr second_arr(0, 0);
    setlocale(LC_ALL, "Russian");
    while (input != 1 && input != 2)
    {
        cout << "Выберите вариант ввода(1 - ручной ввод, 2 - считывание из файла): ";
        cin >> input;
        switch (input)
        {
        case 1:
            first_arr.Input_Arr();
            second_arr.Input_Arr();
            break;
        case 2:
            first_arr.Read_File("arr1.txt");
            second_arr.Read_File("arr2.txt");
            break;
        default:
            cout << "Неверный ввод. Повторите попытку" << endl;
        }
    }
    while (choice != 0)
    {
        cout << "Выберите пункт меню: " << endl;
        cout << endl;
        cout << "1 - Просмотреть 1-й массив" << endl;
        cout << "2 - Просмотреть 2-й массив" << endl;
        cout << "3 - Отсортировать 1-й массив" << endl;
        cout << "4 - Вставить элемент в массив 1-й" << endl;
        cout << "5 - Найти элемент в 1-ом массиве" << endl;
        cout << "6 - Найти объединение массивов" << endl;
        cout << "7 - Найти пересечение массивов" << endl;
        cout << "0 - Завершить программу" << endl;
        cout << endl;
        cout << "Ваш выбор: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            cout << "1 - й массив: " << endl;
            first_arr.View_Arr();
            break;
        }
        case 2:
        {
            cout << "2 - й массив: " << endl;
            second_arr.View_Arr();
            break;
        }
        case 3:
        {
            cout << "Исходный массив: " << endl;
            first_arr.View_Arr();
            first_arr.Sort();
            cout << "Отсортированный массив: " << endl;
            first_arr.View_Arr();
            cout << endl;
            break;
        }
        case 4:
        {
            if (!first_arr.Sort_Check())
            {
                cout << "Массив был отсортирован" << endl;
                first_arr.Sort();
            }
            cout << "Введите место, куда хотите вставить элемент: ";
            cin >> i >> j;
            cout << "Введите значение элемента двумерного массива: ";
            cin >> elem;
            first_arr.Insert_Elem(elem, i, j);
            cout << "Полученный массив: " << endl;
            first_arr.View_Arr();
            break;
        }
        case 5:
        {
            if (!first_arr.Sort_Check())
            {
                cout << "Массив был отсортирован" << endl;
                first_arr.Sort();
            }
            cout << "Введите значение элемента, который хотите найти: ";
            cin >> elem;
            first_arr.Search_Elem(elem);
            cout << endl;
            break;
        }
        case 6:
        {
            if (!first_arr.Sort_Check())
            {
                cout << "1-й массив был отсортирован" << endl;
                first_arr.Sort();
            }
            if (!second_arr.Sort_Check())
            {
                cout << "2-й массив был отсортирован" << endl;
                second_arr.Sort();
            }
            Double_Arr union_arr = first_arr.Union(second_arr);
            cout << "Объединение массивов: " << endl;
            union_arr.View_Arr();
            break;
        }
        case 7:
        {
            if (!first_arr.Sort_Check())
            {
                cout << "1-й массив был отсортирован" << endl;
                first_arr.Sort();
            }
            if (!second_arr.Sort_Check())
            {
                cout << "2-й массив был отсортирован" << endl;
                second_arr.Sort();
            }
            Double_Arr intersection_arr = first_arr.Intersection(second_arr);
            cout << "Пересечение массивов: " << endl;
            intersection_arr.View_Arr();
            break;
        }
        case 0:
        {
            cout << "Работа программы завершена";
            break;
        }
        default:
        {
            cout << "Неверный ввод. Повторите попытку!";
            break;
        }
        }
    }
    return 0;
}