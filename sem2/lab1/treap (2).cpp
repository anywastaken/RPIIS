#include "treap.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iostream>

Treap::Treap() : root(nullptr) {
    std::srand(std::time(0));
}

Treap::~Treap() {
    destroy(root);
}

void Treap::destroy(pitem node) {
    if (node) {
        destroy(node->l);
        destroy(node->r);
        delete node;
    }
}

void Treap::split(pitem t, int key, pitem& l, pitem& r) {
    if (!t)       //если узел t равен nullptr, то исходное дерево пусто
        l = r = nullptr;
    else if (key < t->key)
        split(t->l, key, l, t->l), r = t;
    else
        split(t->r, key, t->r, r), l = t;
}

void Treap::insert(pitem& t, pitem it) {
    if (!t)
        t = it;
    else if (it->prior > t->prior)
        split(t, it->key, it->l, it->r), t = it;
    else
        insert(it->key < t->key ? t->l : t->r, it);
}

//Если одно из поддеревьев l или r пустое, то результатом объединения(t) становится непустое поддерево.
void Treap::merge(pitem& t, pitem l, pitem r) {
    if (!l || !r)
        t = l ? l : r;
    else if (l->prior > r->prior)
        merge(l->r, l->r, r), t = l;
    else
        merge(r->l, l, r->l), t = r;
}

void Treap::erase(pitem& t, int key) {
    if (!t) return; // Проверка на nullptr
    if (t->key == key)
        merge(t, t->l, t->r);
    else
        erase(key < t->key ? t->l : t->r, key);
}

pitem Treap::unite(pitem l, pitem r) {
    if (!l || !r) return l ? l : r;
    if (l->prior < r->prior) std::swap(l, r);
    pitem lt, rt;
    split(r, l->key, lt, rt);
    l->l = unite(l->l, lt);  //Рекурсивно объединяем левое поддерево l с поддеревом lt и правое поддерево l с поддеревом rt
    l->r = unite(l->r, rt);
    return l;
}

void Treap::insert(int key) {
    if (find(key)) return; // Проверка на дубликаты
    pitem it = new item(key, std::rand());
    insert(root, it);
}

pitem Treap::find(int key) {
    pitem t = root;
    while (t) {
        if (t->key == key)
            return t;
        t = key < t->key ? t->l : t->r;
    }
    return nullptr;
}

void Treap::remove(int key) {
    erase(root, key);
}

void Treap::buildFromArray(int arr[], int size) {
    for (int i = 0; i < size; ++i) {
        insert(arr[i]);
    }
}

Treap* Treap::merge(Treap* other) {
    Treap* newTreap = new Treap();
    newTreap->root = unite(this->root, other->root);
    // Очищаем корни исходных деревьев, чтобы избежать двойного удаления
    this->root = nullptr;
    other->root = nullptr;
    return newTreap;
}

Treap* Treap::intersect(Treap* other) {
    Treap* newTreap = new Treap();
    newTreap->root = intersect(this->root, other->root);
    return newTreap;
}

pitem Treap::intersect(pitem t1, pitem t2) {
    if (!t1 || !t2) return nullptr;

    if (t1->key == t2->key) {
        pitem newNode = new item(t1->key, std::rand());
        newNode->l = intersect(t1->l, t2->l);
        newNode->r = intersect(t1->r, t2->r);
        return newNode;
    } else if (t1->key < t2->key) {
        // Ищем пересечение в правом поддереве t1 и текущем t2
        pitem right = intersect(t1->r, t2);
        // Ищем пересечение в текущем t1 и левом поддереве t2
        pitem left = intersect(t1, t2->l);
        // Объединяем результаты
        return mergeNodes(left, right);
    } else {
        // Ищем пересечение в левом поддереве t1 и текущем t2
        pitem left = intersect(t1->l, t2);
        // Ищем пересечение в текущем t1 и правом поддереве t2
        pitem right = intersect(t1, t2->r);
        // Объединяем результаты
        return mergeNodes(left, right);
    }
}

pitem Treap::mergeNodes(pitem l, pitem r) {
    if (!l) return r;
    if (!r) return l;
    if (l->prior > r->prior) {
        l->r = mergeNodes(l->r, r);
        return l;
    } else {
        r->l = mergeNodes(l, r->l);
        return r;
    }
}