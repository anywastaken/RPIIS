#ifndef BTREE_HPP
#define BTREE_HPP

#include <iostream>
#include <vector>

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

#endif
