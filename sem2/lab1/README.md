# Лабораторная работа №1
## Цель: 
Разработать библиотеку для работы с  N-арным деревом на выбранном императивном языке программирования (например, C++, Java, Python).
## Задача:
B-Дерево. Поиск. Вставка узла в дерево. Удаление узла из дерева.
## Определения:
_Дерево_ — связный ациклический граф.[1] Связность означает наличие маршрута между любой парой вершин, ацикличность — отсутствие циклов.

_B-дерево – это сбалансированное дерево поиска, в котором каждый узел содержит множество ключей и имеет более двух потомков.
Реализация

### Структура KeyPair
Структура KeyPair представляет собой пару ключей key1 и key2. Для этой структуры перегружены операторы < и ==, что позволяет сравнивать объекты KeyPair между собой. Это необходимо для корректной работы операций вставки, поиска и удаления в B-дереве.
```c++
struct KeyPair {
    int key1;
    int key2;

    bool operator<(const KeyPair& other) const {
        return key1 < other.key1 || (key1 == other.key1 && key2 < other.key2);
    }

    bool operator==(const KeyPair& other) const {
        return key1 == other.key1 && key2 == other.key2;
    }
};
```
### Класс BTreeNode
класс BTreeNode представляет узел B-дерева. Каждый узел содержит:

##### 1.Массив данных data, где хранятся пары ключей.
##### 2.Массив указателей на дочерние узлы children.
##### 3.Поле numKeys, которое указывает количество ключей в узле.
##### 4.Поле leaf, которое указывает, является ли узел листом.
##### 5.Конструктор BTreeNode инициализирует узел, выделяя память для данных и дочерних узлов. Деструктор освобождает выделенную память.

Конструктор BTreeNode инициализирует узел, выделяя память для данных и дочерних узлов. Деструктор освобождает выделенную память.
```c++
class BTreeNode {
public:
    KeyPair* data;
    BTreeNode** children;
    int numKeys;
    bool leaf;
    static const int M = 3; // Минимальная степень дерева

    BTreeNode(bool isLeaf);
    void insertNonFull(const KeyPair& kp);
    void splitChild(int i, BTreeNode* y);
    bool search(const KeyPair& kp);
    void remove(const KeyPair& kp);
    ~BTreeNode();

private:
    void removeFromLeaf(int idx);
    void removeFromNonLeaf(int idx);
    KeyPair getPredecessor(int idx);
    KeyPair getSuccessor(int idx);
    void fill(int idx);
    void borrowFromPrev(int idx);
    void borrowFromNext(int idx);
    void merge(int idx);
};
```
### Методы класса BTreeNode

##### insertNonFull(const KeyPair& kp): Вставляет ключ в неполный узел. Если узел является листом, ключ добавляется в массив данных. Если узел не является листом, происходит рекурсивный вызов для соответствующего дочернего узла.
##### splitChild(int i, BTreeNode* y): Разделяет дочерний узел y на два узла. Этот метод вызывается, когда дочерний узел заполнен.
##### search(const KeyPair& kp): Рекурсивно ищет ключ в дереве. Если ключ найден в текущем узле, возвращается true. Если узел является листом и ключ не найден, возвращается false.
##### remove(const KeyPair& kp): Удаляет ключ из узла. Если ключ находится в листе, он удаляется непосредственно. Если ключ находится в нелистовом узле, происходит рекурсивное удаление.
##### removeFromLeaf(int idx): Удаляет ключ из листа.
##### removeFromNonLeaf(int idx): Удаляет ключ из нелистового узла.
##### getPredecessor(int idx) и getSuccessor(int idx): Возвращают предшественника и преемника ключа соответственно.
##### fill(int idx): Заполняет дочерний узел, если в нем недостаточно ключей.
##### borrowFromPrev(int idx) и borrowFromNext(int idx): Заимствуют ключи у соседних узлов.
##### merge(int idx): Объединяет два узла.

### Класс BTree
Класс BTree представляет само B-дерево. Он содержит указатель на корневой узел и методы для вставки, поиска, удаления и вывода дерева.
```c++
class BTree {
public:
    BTreeNode* root;

    BTree();
    void insert(int key1, int key2);
    bool search(int key1, int key2);
    void remove(int key1, int key2);
    void print();
    ~BTree();

private:
    void printTree(BTreeNode* node, int level);
};
```

