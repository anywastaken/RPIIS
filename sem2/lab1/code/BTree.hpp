#pragma once
#ifndef BTREE_HPP
#define BTREE_HPP

#include <iostream>

class BTreeNode {
    int* keys;
    int t;
    BTreeNode** children;
    int n;
    bool leaf;
public:
    BTreeNode(int t, bool leaf);
    void traverse();
    BTreeNode* search(int k);
    void insertNonFull(int k);
    void splitChild(int i, BTreeNode* y);
    void remove(int k);
    int findKey(int k);
    void removeFromLeaf(int idx);
    void removeFromNonLeaf(int idx);
    int getPred(int idx);
    int getSucc(int idx);
    void fill(int idx);
    void borrowFromPrev(int idx);
    void borrowFromNext(int idx);
    void merge(int idx);

    friend class BTree;
};

class BTree {
    BTreeNode* root;
    int t;
public:
    BTree(int t = 3);
    void traverse();
    BTreeNode* search(int k);
    void insert(int k);
    void remove(int k);
};

#endif BTREE_HPP
