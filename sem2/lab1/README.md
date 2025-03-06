<h1>Лабараторная работа #1</h1>

## Цели работы:

* Изучить основные понятия, связанные с особым типом сбалансированного дерева поиска - B-деревом
* Научиться реализовывать основные алгоритмы при работе с B-деревом

## Задачи:

* Разработать библиотеку для работы со структурой данных "B-дерево" на любом императивнойм языке программирования
* Разработать тестовую программу, которая демонстрирует работоспособность реализованной библиотеки

## Вариант:

6. B-Дерево. Поиск. Вставка. Удаление.

## Понятие B-дерева:

<h4>B-дерево - структура данных, дерево поиска, удовлетворяющее основным свойствам:</h3>

* В нодах(от node - узел) содержатся массивы вида [UXUXU], где U - указатель на следующую ноду или nullptr, X - ключи
* Количество указатлей в ноде = количество ключей + 1
* Степень дерева(m) - количество указателей в ноде
* Минимальная степень дерева(t) = степень дерева / 2 (округлённое к большему): t = ceil(m/2)
* Все указатели на одном уровне либо указывают на nullptr, либо указывают на следующую ноду
* Все листья дерева находятся на одном уровне => B-дерево всегда сбалансированно
* Дерево растёт вверх
* Корневая нода может содержать от 1 до 2t-1 ключей
* Корневая нода может иметь от 2 до 2t дочерние ноды
* Левый указатель отдельно взятого ключа всегда указывает на меьнший по номеру ключ, а правый - на больший

*На картинке ниже представлено В-дерево со степенью 4*

<p align="center">
   <img alt="Пример B-дерева" src="https://github.com/iis-42x70x/RPIIS/blob/Говор_Г/sem2/lab1/img/1.png">
</p>

## Структура программы:

<p align="center">
   <img alt="Пример B-дерева" src="https://github.com/iis-42x70x/RPIIS/blob/Говор_Г/sem2/lab1/img/2.png">
</p>

### Прилагаемые файлы:
* [main.cpp](https://github.com/iis-42x70x/RPIIS/blob/Говор_Г/sem2/lab1/code/main.cpp) - тесты
* [BTree.cpp](https://github.com/iis-42x70x/RPIIS/blob/Говор_Г/sem2/lab1/code/BTree.cpp) - реализация
* [BTree.hpp](https://github.com/iis-42x70x/RPIIS/blob/Говор_Г/sem2/lab1/code/BTree.hpp) - декларация

## Тесты:
* Тест 1
  
<p align="center">
   <img width = "700px" alt="Пример B-дерева" src="https://github.com/iis-42x70x/RPIIS/blob/Говор_Г/sem2/lab1/img/4.1.png">
</p>

* Тест 2
  
<p align="center">
   <img width = "700px" alt="Пример B-дерева" src="https://github.com/iis-42x70x/RPIIS/blob/Говор_Г/sem2/lab1/img/4.2.png">
</p>

* Тест 3
  
<p align="center">
   <img width = "700px" alt="Пример B-дерева" src="https://github.com/iis-42x70x/RPIIS/blob/Говор_Г/sem2/lab1/img/4.3.png">
</p>

* Тест 4
  
<p align="center">
   <img width = "700px" alt="Пример B-дерева" src="https://github.com/iis-42x70x/RPIIS/blob/Говор_Г/sem2/lab1/img/4.4.png">
</p>

* Тест 5
  
<p align="center">
   <img width = "700px" alt="Пример B-дерева" src="https://github.com/iis-42x70x/RPIIS/blob/Говор_Г/sem2/lab1/img/4.5.png">
</p>

## Алгоритмы программы (BTree.cpp): 

* Обход дерева
  
```C++
void BTreeNode::traverse() {
    int i;
    for (i = 0; i < n; i++) {
        if (!leaf) children[i]->traverse();
        std::cout << keys[i] << " ";
    }
    if (!leaf) children[i]->traverse();
}

void BTree::traverse() {
    if (root) root->traverse();
}
```

* Поиск ключа в дереве
  
```C++
BTreeNode* BTreeNode::search(int k) {
    int i = 0;
    while (i < n && k > keys[i]) i++;
    if (keys[i] == k) return this;
    if (leaf) return nullptr;
    return children[i]->search(k);
}

BTreeNode* BTree::search(int k) {
    return root ? root->search(k) : nullptr;
}
```

* Вставка ключа
  
```C++
void BTree::insert(int k) {
    if (!root) {
        root = new BTreeNode(t, true);
        root->keys[0] = k;
        root->n = 1;
    }
    else {
        if (root->n == 2 * t - 1) {
            BTreeNode* s = new BTreeNode(t, false);
            s->children[0] = root;
            s->splitChild(0, root);
            int i = (s->keys[0] < k) ? 1 : 0;
            s->children[i]->insertNonFull(k);
            root = s;
        }
        else {
            root->insertNonFull(k);
        }
    }
}
```

* Вставка ключа, если нода заполнена не до конца(<2t-1)

```C++
void BTreeNode::insertNonFull(int k) {
    int i = n - 1;
    if (leaf) {
        while (i >= 0 && keys[i] > k) {
            keys[i + 1] = keys[i];
            i--;
        }
        keys[i + 1] = k;
        n++;
    }
    else {
        while (i >= 0 && keys[i] > k) i--;
        if (children[i + 1]->n == 2 * t - 1) {
            splitChild(i + 1, children[i + 1]);
            if (keys[i + 1] < k) i++;
        }
        children[i + 1]->insertNonFull(k);
    }
}
```

* Разбиение детей(Если это требуется)
  
```C++
void BTreeNode::splitChild(int i, BTreeNode* y) {
    BTreeNode* z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;
    for (int j = 0; j < t - 1; j++) z->keys[j] = y->keys[j + t];
    if (!y->leaf) {
        for (int j = 0; j < t; j++) z->children[j] = y->children[j + t];
    }
    y->n = t - 1;
    for (int j = n; j >= i + 1; j--) children[j + 1] = children[j];
    children[i + 1] = z;
    for (int j = n - 1; j >= i; j--) keys[j + 1] = keys[j];
    keys[i] = y->keys[t - 1];
    n++;
}
```

* Удаление ключа
  
```C++
void BTree::remove(int k) {
    if (!root) return;
    root->remove(k);
    if (root->n == 0) {
        BTreeNode* tmp = root;
        root = root->leaf ? nullptr : root->children[0];
        delete tmp;
    }
}

void BTreeNode::remove(int k) {
    int idx = findKey(k);
    if (idx < n && keys[idx] == k) {
        if (leaf) removeFromLeaf(idx);
        else removeFromNonLeaf(idx);
    }
    else {
        if (leaf) return;
        bool lastChild = (idx == n);
        if (children[idx]->n < t) fill(idx);
        if (lastChild && idx > n) children[idx - 1]->remove(k);
        else children[idx]->remove(k);
    }
}
```

## Вывод:
* Мной была разработана библиотека по работе с B-деревьями. В ней я реализовал основные операции над B-деревом: вставка ключа, удаление ключа, поиск ключа, обход дерева.

## Материалы и сточники:

* [YouTube](https://www.youtube.com/watch?v=WXXetwePSRk) - подробное объяснение принципа работы с B-деревьями от Volodya Mozhenkov с помощью видиоматериалы
* [Викиконспекты](https://neerc.ifmo.ru/wiki/index.php?title=B-дерево) - особенности реализации B-деревьев на C++
* [Draw.io](draw.io) - платформа для составление схем, блок-схем
