#include <iostream>

using namespace std;

int Check(int el, int* mas, int size)
{
    int koll = 0;
    for (int i = 0; i < size; i++) {
        if (mas[i] == el) koll++;
    }

    return koll;
}

void Create(int* mas, int size)
{
    bool uniq = true;
    while (uniq) {
        uniq = false;
        for (int i = 0; i < size; i++) {
            cout << "Введите " << i + 1 << " элемент множества: ";
            cin >> mas[i];
        }
        for (int i = 0; i < size; i++) {
            if (Check(mas[i], mas, size) > 1) {
                uniq = true;
                cout << "Элементы множества не могут повторяться! Попробуйте снова" << endl;
                break;
            }
        }
    }
}

void View(int* mas, int size)
{
    cout << "{";
    for (int i = 0; i < size; i++) {
        cout << mas[i];
        if (i < size - 1) cout << ", ";
    }
    cout << "}" << endl;
}

void Add(int*& mas, int& size)
{
    int el;
    cout << "Введите элемент, который хотите добавить: ";
    cin >> el;

    if (Check(el, mas, size) == 1) {
        cout << "Данный элемент уже есть в данном множестве" << endl;
        return;
    }

    int* Mas = new int[size + 1];
    for (int i = 0; i < size; i++) {
        Mas[i] = mas[i];
    }
    Mas[size] = el;

    delete[]mas;

    size++;
    mas = Mas;
    cout << "Новое множество = "; View(mas, size);
}

void Delete(int*& mas, int& size)
{
    int el;
    cout << "Введите элемент, который хотите удалить: ";
    cin >> el;

    if (Check(el, mas, size) != 1) {
        cout << "Данного элемента нет в данном множестве" << endl;
        return;
    }

    int* Mas = new int[size - 1];
    int j = 0;
    for (int i = 0; i < size; i++) {
        if (mas[i] != el) Mas[j++] = mas[i];
    }

    delete[]mas;

    size--;
    mas = Mas;
    cout << "Новое множество = "; View(mas, size);
}

void Intersection(int* A, int* B, int a, int b)
{
    cout << "{";
    bool first = true;
    for (int i = 0; i < a; i++) {
        if (Check(A[i], B, b) == 1) {
            if (!first) cout << ", ";
            cout << A[i];
            first = false;
        }
    }
    cout << "}" << endl;
}

void Association(int* A, int* B, int a, int b)
{
    cout << "{";
    bool first = true;
    for (int i = 0; i < a; i++) {
        if (!first) cout << ", ";
        cout << A[i];
        first = false;
    }
    for (int i = 0; i < b; i++) {
        if (Check(B[i], A, a) != 1) {
            cout << ", " << B[i];
        }
    }
    cout << "}" << endl;
}

int main() {
    setlocale(LC_ALL, "RU");

    int a, b, k, k1, k2, k3, el;

    cout << "Введите количество элементов множества A: ";
    cin >> a;
    int* A = new int[a];
    Create(A, a);
    cout << "A = "; View(A, a); cout << endl;

    cout << "Введите количество элементов множества B: ";
    cin >> b;
    int* B = new int[b];
    Create(B, b);
    cout << "B = "; View(B, b); cout << endl;

    do {
        cout << "1. Добавление элемента во множество" << endl;
        cout << "2. Удаление элемента из множества" << endl;
        cout << "3. Поиск элемента во множестве" << endl;
        cout << "4. Пересечение двух множеств" << endl;
        cout << "5. Объединение двух множеств" << endl;
        cout << "0. Выход" << endl;

        cin >> k;
        switch (k) {
        case 1:
            cout << "1. Во множество A" << endl;
            cout << "2. Во множество B" << endl;
            cin >> k1;
            if (k1 == 1) {
                Add(A, a);
            }
            else if (k1 == 2) {
                Add(B, b);
            }
            break;
        case 2:
            cout << "1. Из множества A" << endl;
            cout << "2. Из множества B" << endl;
            cin >> k2;
            if (k2 == 1) {
                Delete(A, a);
            }
            else if (k2 == 2) {
                Delete(B, b);
            }
            break;
        case 3:
            cout << "1. Во множестве A" << endl;
            cout << "2. Во множестве B" << endl;
            cin >> k3;
            if (k3 == 1) {
                cout << "Введите элемент, который хотите проверить на наличие во множестве A: ";
                cin >> el;
                if (Check(el, A, a) == 1) cout << "Данный элемент есть во множестве A" << endl;
                else cout << "Данного элемента нет во множестве A" << endl;
            }
            else if (k3 == 2) {
                cout << "Введите элемент, который хотите проверить на наличие во множестве B: ";
                cin >> el;
                if (Check(el, B, b) == 1) cout << "Данный элемент есть во множестве B" << endl;
                else cout << "Данного элемента нет во множестве B" << endl;
            }
            break;
        case 4:
            cout << "Пересечение множеств A и B = ";
            Intersection(A, B, a, b);
            break;
        case 5:
            cout << "Объединение множеств A и B = ";
            Association(A, B, a, b);
            break;
        case 0:
            cout << "Выход из программы" << endl;
            break;
        default:
            cout << "Некорректный выбор" << endl;
            break;
        }
    } while (k != 0);

    delete[]A;
    delete[]B;

    return 0;
}
