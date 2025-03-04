# Лабораторная работа №1
## Цель: 
Разработать библиотеку для работы с структурой данных Бор на выбранном императивном языке программирования
## Задача:
Бор. Вставка строки в бор. Удаление строки из бора. Поиск строки в боре.
## Определения:
_Бор_ — структура данных для хранения набора строк, представляющая из себя подвешенное дерево с символами на рёбрах.

_Дерево_ — связный ациклический граф. Связность означает наличие маршрута между любой парой вершин, ацикличность — отсутствие циклов.
Реализация
### Класс Bor
В началек кода представлен класс ```Bor```, в котором определены структра узлов и прототипы основных функции. Каждый узел содержит значение ```WordEnd```, которое отвечает за обозначение конца слова, и массив ```children``` из 26 указателей для каждой буквы английского алфавита.
```c++
#include <iostream>
#include <vector>
class Bor {
private:
	struct BorNode {
		std::vector<BorNode*> children;
		bool WordEnd;
		BorNode() : children(26, NULL), WordEnd(false){} 
	};
	BorNode* root;
	void delBor(BorNode* node);
	int Index(char ch) const;
	bool removeHelper(BorNode* root, const std::string& word, int depth);
public:
	Bor();
	~Bor();
	void insert(const std::string& word);
	bool search(const std::string& word) const;
	void remove(const std::string& word);
};
void menu();
```
### Функуия вставки элемента в Бор  
## Разбор функции `Bor::insert`

Эта функция добавляет слово в бор (префиксное дерево). Давайте разберем код построчно:

```cpp
void Bor::insert(const std::string& word) {
```
Функция `insert` принимает на вход строку `word` (слово), которое нужно вставить в бор.

```cpp
    BorNode* node = root;
```
Создаем указатель `node` и устанавливаем его в корень дерева (`root`). Мы будем перемещаться по дереву, начиная с корневого узла.

```cpp
    for (char ch : word) {
```
Запускаем цикл `for`, который перебирает каждый символ `ch` из строки `word`.

```cpp
        int index = Index(ch);
```
Вычисляем индекс `index` для символа `ch`, который определяет, в какой ячейке массива `children` (потомков) должен находиться этот символ.

```cpp
        if (!node->children[index]) {
            node->children[index] = new BorNode;
        }
```
Если в `children[index]` еще нет узла (т. е. указатель `NULL`), создаем новый узел `BorNode` и сохраняем его в этом месте.

```cpp
        node = node->children[index];
```
Переходим к следующему узлу (перемещаемся глубже в дерево).

```cpp
    }
```
После завершения цикла весь путь по дереву пройден, и мы оказались в узле, который соответствует последнему символу вставляемого слова.

```cpp
    node->WordEnd = true;
```
Помечаем текущий узел как конец слова (`WordEnd = true`). Это означает, что в этом узле заканчивается полноценное слово, а не просто его часть.


Вот разбор всех функций в формате **Markdown**:  

---

## `Bor::search`

Эта функция выполняет **поиск слова** в боре.  

### Код:
```cpp
bool Bor::search(const std::string& word) const {
    BorNode* node = root;
    for (char ch : word) {
        int index = Index(ch);
        if (!node->children[index]) {
            return false;
        }
        node = node->children[index];
    }
    return node->WordEnd;
}
```

### Разбор:
1. **Начинаем поиск с корневого узла**:
   ```cpp
   BorNode* node = root;
   ```
   Устанавливаем `node` в корень.

2. **Идем по каждому символу слова**:
   ```cpp
   for (char ch : word) {
   ```
   Перебираем символы строки.

3. **Вычисляем индекс символа**:
   ```cpp
   int index = Index(ch);
   ```
   Индекс определяет положение символа в массиве `children`.

4. **Проверяем, существует ли нужный узел**:
   ```cpp
   if (!node->children[index]) {
       return false;
   }
   ```
   Если узел отсутствует, значит слово **не найдено**.

5. **Переходим к следующему узлу**:
   ```cpp
   node = node->children[index];
   ```

6. **Проверяем, является ли узел концом слова**:
   ```cpp
   return node->WordEnd;
   ```
   Если `WordEnd = true`, слово **существует** в боре.

---

## `Bor::delBor`

Эта функция **рекурсивно удаляет** все узлы дерева.

### Код:
```cpp
void Bor::delBor(BorNode* node) {
    for (BorNode* child : node->children) {
        if (child != NULL) {
            delBor(child);
        }
    }
    delete node;
}
```

### Разбор:
1. **Перебираем всех потомков узла**:
   ```cpp
   for (BorNode* child : node->children) {
   ```
   Проходим по всем дочерним узлам.

2. **Рекурсивно удаляем каждого потомка**:
   ```cpp
   if (child != NULL) {
       delBor(child);
   }
   ```
   Если `child` не `NULL`, вызываем `delBor(child)`.

3. **Удаляем сам узел**:
   ```cpp
   delete node;
   ```
   После удаления всех потомков удаляем сам узел.

---

## `Bor::removeHelper`

Эта функция **помогает удалить слово** из бора.

### Код:
```cpp
bool Bor::removeHelper(BorNode* node, const std::string& word, int depth) {
    if (!node) return false;
    if (depth == word.size()) {
        if (!node->WordEnd) return false; 
        node->WordEnd = false;
        return node->children.empty(); 
    }

    int index = Index(word[depth]);
    if (index == -1 || !node->children[index]) return false;

    bool shouldDeleteChild = removeHelper(node->children[index], word, depth + 1);

    if (shouldDeleteChild) {
        delete node->children[index];
        node->children[index] = NULL;
        return node->children.empty() && !node->WordEnd;
    }

    return false;
}
```

### Разбор:
1. **Базовый случай**: если `node == NULL`, вернуть `false`.

2. **Если дошли до конца слова**:
   ```cpp
   if (depth == word.size()) {
   ```
   Проверяем, что мы в последнем символе слова.

3. **Снимаем метку конца слова**:
   ```cpp
   node->WordEnd = false;
   ```
   Убираем флаг `WordEnd`.

4. **Рекурсивно спускаемся по дереву**:
   ```cpp
   bool shouldDeleteChild = removeHelper(node->children[index], word, depth + 1);
   ```
   Вызываем удаление следующего символа.

5. **Если потомок пуст, удаляем его**:
   ```cpp
   if (shouldDeleteChild) {
       delete node->children[index];
       node->children[index] = NULL;
   }
   ```
   Если узел **больше не нужен**, удаляем его.

---

## `Bor::remove`

Функция **удаляет слово**, используя `removeHelper`.

### Код:
```cpp
void Bor::remove(const std::string& word) {
    removeHelper(root, word, 0);
}
```

### Разбор:
1. Просто вызывает `removeHelper` с начального узла.

---

## `Bor::Index`

Функция **определяет индекс символа** в массиве `children`.

### Код:
```cpp
int Bor::Index(char ch) const {
    if (ch >= 'a' && ch <= 'z') return ch - 'a';      
    if (ch >= 'A' && ch <= 'Z') return ch - 'A';       
    return -1; 
}
```

### Разбор:
1. **Для строчных букв (a-z)**:
   ```cpp
   if (ch >= 'a' && ch <= 'z') return ch - 'a';
   ```
   Индекс от `0` до `25`.

2. **Для заглавных букв (A-Z)**:
   ```cpp
   if (ch >= 'A' && ch <= 'Z') return ch - 'A';
   ```
   Индекс от `0` до `25`.

3. **Иначе возвращаем `-1`** (символ не поддерживается).

---

## `menu()`

Функция **создает меню** для работы с бором.

### Код:
```cpp
void menu() {
    Bor bor;
    int sel;
    std::string word;
    while (true) {
        std::cout << "Select option: " << std::endl;
        std::cout << "1. Add string" << std::endl;
        std::cout << "2. Search string" << std::endl;
        std::cout << "3. Remove string" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cin >> sel;
        switch (sel)
        {
        case 1: {
            std::cout << "Enter string: ";
            std::cin >> word;
            bor.insert(word);
            break;
        }
        case 2: {
            std::cout << "Enter string: ";
            std::cin >> word;
            if (bor.search(word)) {
                std::cout << "The word exists in the bor." << std::endl;
            }
            else {
                std::cout << "The word does not exist in the bor." << std::endl;
            }
            break;
        }
        case 3: {
            std::cout << "Enter string: ";
            std::cin >> word;
            bor.remove(word);
            std::cout << "Word removed.";
            break;
        }
        case 4: {
            return;
        }
        default:
            std::cout << "Incorrect option";
            break;
        }
    }
}
```

### Разбор:
1. **Выводит меню и ждет ввод команды**:
   ```cpp
   std::cout << "Select option: " << std::endl;
   std::cin >> sel;
   ```

2. **Добавляет слово**:
   ```cpp
   case 1:
       std::cin >> word;
       bor.insert(word);
   ```

3. **Ищет слово**:
   ```cpp
   case 2:
       std::cin >> word;
       if (bor.search(word)) ...
   ```

4. **Удаляет слово**:
   ```cpp
   case 3:
       std::cin >> word;
       bor.remove(word);
   ```

5. **Завершает работу**:
   ```cpp
   case 4:
       return;
   ```

---

### Вывод
Реализованные функции позволяют эффективно вставлять, удалять и искать строки в Боре.
