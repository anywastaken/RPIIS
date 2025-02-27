#include "Graph.h"

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

    void Graph::InputMatrix() {
        cout << "Введите количество вершин и дуг: ";
        cin >> n >> m;

        matrix.resize(n, vector<int>(m, 0));

        cout << "Введите элементы матрицы инцидентности (" << n << " строк и " << m << " столбцов):\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> matrix[i][j];
            }
        }
    }

    void Graph::PrintMatrix() {
        cout << "\nМатрица инцидентности:" << endl;
        for (const auto& row : matrix) {
            for (int val : row) {
                cout << val << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    void Graph::AddVertex() {
        vector<int> newVertex(m, 0);
        matrix.push_back(newVertex);
        n++;
        cout << "Вершина добавлена." << endl << endl;
    }

    void Graph::DelVertex() {
        int numVertex;
        cout << endl << "Выберите вершину, которую хотите удалить: " << endl;
        cin >> numVertex;

        numVertex--;
        if (numVertex >= 0 && numVertex < n) {
            for (int i = matrix[0].size() - 1; i >= 0; i--) {
                if (matrix[numVertex][i] != 0) {
                    for (int k = 0; k < n; k++) {
                        matrix[k].erase(matrix[k].begin() + i);
                    }
                    m--;
                }
            }
            matrix.erase(matrix.begin() + numVertex);
            cout << "Вершина " << numVertex + 1 << " удалена." << endl;
            n--;
        }
        else {
            cout << "Недопустимый индекс для удаления элемента." << endl;
            return;
        }
    }

    void Graph::AddArc() {
        int fromVertex, toVertex;
        cout << endl << "Введите 2 вершины, от которой и до которой будет проведена дуга: " << endl;
        cin >> fromVertex >> toVertex;
        fromVertex--;
        toVertex--;

        if (fromVertex == toVertex) {
            cout << "Невозможно создать петлю. Введите 2 корректных индекса." << endl;
            return;
        }

        if ((fromVertex >= 0 && fromVertex < n) && (toVertex >= 0 && toVertex < n)) {
            for (int i = 0; i < n; i++) {
                if (i == fromVertex) {
                    matrix[i].push_back(-1);
                }
                else if (i == toVertex) {
                    matrix[i].push_back(1);
                }
                else {
                    matrix[i].push_back(0);
                }
            }
            m++;
            cout << "Дуга от вершины " << fromVertex + 1 << " до вершины " << toVertex + 1 << " добавлена." << endl;
        }
        else {
            cout << "Недопустимый индекс." << endl;
            return;
        }
    }

    void Graph::DelArc() {
        int numArc;
        cout << endl << "Введите номер дуги, которую хотите удалить: " << endl;
        cin >> numArc;

        if (numArc > 0 && numArc <= m) { // Исправлено на m
            for (int i = 0; i < n; i++) {
                matrix[i].erase(matrix[i].begin() + numArc - 1);
            }
            m--;
            cout << "Дуга удалена." << endl;
        }
        else {
            cout << "Недопустимый индекс." << endl;
            return;
        }
    }

    void Graph::BFS() {
        int firstVertex;
        cout << "Введите номер вершины, с которой начать обход в ширину: ";
        cin >> firstVertex;

        if (cin.fail() || firstVertex < 1 || firstVertex > n) { // Исправлено условие
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Некорректный ввод." << endl;
            return;
        }

        firstVertex--; // Приводим к индексу 0
        queue<int> q;
        vector<bool> visited(n, false); // Отслеживаем посещенные вершины

        q.push(firstVertex);
        visited[firstVertex] = true;

        cout << "Результат обхода в ширину: ";

        while (!q.empty()) {
            int current = q.front();
            q.pop();
            cout << current + 1 << " "; // Выводим номер вершины (обратно к 1-индексации)

            // Проверяем все дуги для текущей вершины
            for (int i = 0; i < m; i++) {
                if (matrix[current][i] != 0) { // Если есть дуга
                    int adjacentVertex = (matrix[current][i] == -1) ? i : -1; // Определяем смежную вершину
                    if (adjacentVertex != -1 && !visited[adjacentVertex]) {
                        q.push(adjacentVertex);
                        visited[adjacentVertex] = true;
                    }
                }
            }
        }
        cout << endl;
    }
    void Graph::ShowMenu() {
        cout << "=== Меню ===\n";
        cout << "1. Вывести матрицу\n";
        cout << "2. Добавить вершину\n";
        cout << "3. Удалить вершину\n";
        cout << "4. Добавить дугу\n";
        cout << "5. Удалить дугу\n";
        cout << "6. Обойти граф в ширину\n";
        cout << "7. Выход\n";
        cout << "Выберите опцию: ";
    }
    void Graph::prog() {
        setlocale(LC_ALL, "ru");
        Graph graph;
        graph.InputMatrix();
        int choice;
        do {
            ShowMenu();
            cin >> choice;
            switch (choice) {
            case 1: graph.PrintMatrix(); break;
            case 2: graph.AddVertex(); break;
            case 3: graph.DelVertex(); break;
            case 4: graph.AddArc(); break;
            case 5: graph.DelArc(); break;
            case 7: cout << "До свидания!" << endl; break;
            default: cout << "Неверный выбор." << endl; break;
            }
        } while (choice != 7);
        return;

    }
