#include "BTree.hpp"

BTreeNode::BTreeNode(bool isLeaf) : leaf(isLeaf), numKeys(0) {
    data = new KeyPair[2 * M - 1];
    children = new BTreeNode*[2 * M]();
}

BTreeNode::~BTreeNode() {
    delete[] data;
    delete[] children;
}

void BTreeNode::insertNonFull(const KeyPair& kp) {
    int i = numKeys - 1;

    if (leaf) {
        while (i >= 0 && kp < data[i]) {
            data[i + 1] = data[i];
            i--;
        }
        data[i + 1] = kp;
        numKeys++;
    } else {
        while (i >= 0 && kp < data[i]) {
            i--;
        }
        i++;

        if (children[i]->numKeys == 2 * M - 1) {
            splitChild(i, children[i]);
            if (data[i] < kp) {
                i++;
            }
        }
        children[i]->insertNonFull(kp);
    }
}

void BTreeNode::splitChild(int i, BTreeNode* y) {
    BTreeNode* z = new BTreeNode(y->leaf);
    z->numKeys = M - 1;

    for (int j = 0; j < M - 1; j++) {
        z->data[j] = y->data[j + M];
    }

    if (!y->leaf) {
        for (int j = 0; j < M; j++) {
            z->children[j] = y->children[j + M];
        }
    }

    y->numKeys = M - 1;

    for (int j = numKeys; j >= i + 1; j--) {
        children[j + 1] = children[j];
    }
    children[i + 1] = z;

    for (int j = numKeys - 1; j >= i; j--) {
        data[j + 1] = data[j];
    }
    data[i] = y->data[M - 1];
    numKeys++;
}

bool BTreeNode::search(const KeyPair& kp) {
    int i = 0;
    while (i < numKeys && data[i] < kp) {
        i++;
    }
    if (i < numKeys && data[i] == kp) {
        return true;
    }
    return leaf ? false : children[i]->search(kp);
}

void BTreeNode::remove(const KeyPair& kp) {
    int idx = 0;
    while (idx < numKeys && data[idx] < kp) {
        idx++;
    }

    if (idx < numKeys && data[idx] == kp) {
        if (leaf) {
            removeFromLeaf(idx);
        } else {
            removeFromNonLeaf(idx);
        }
    } else {
        if (leaf) {
            std::cout << "Ключ (" << kp.key1 << ", " << kp.key2 << ") не найден.\n";
            return;
        }

        bool isLast = (idx == numKeys);
        if (children[idx]->numKeys < M) {
            fill(idx);
        }

        if (isLast && idx > numKeys) {
            children[idx - 1]->remove(kp);
        } else {
            children[idx]->remove(kp);
        }
    }
}

void BTreeNode::removeFromLeaf(int idx) {
    for (int i = idx + 1; i < numKeys; i++) {
        data[i - 1] = data[i];
    }
    numKeys--;
}

void BTreeNode::removeFromNonLeaf(int idx) {
    KeyPair key = data[idx];

    if (children[idx]->numKeys >= M) {
        KeyPair pred = getPredecessor(idx);
        data[idx] = pred;
        children[idx]->remove(pred);
    } else if (children[idx + 1]->numKeys >= M) {
        KeyPair succ = getSuccessor(idx);
        data[idx] = succ;
        children[idx + 1]->remove(succ);
    } else {
        merge(idx);
        children[idx]->remove(key);
    }
}

KeyPair BTreeNode::getPredecessor(int idx) {
    BTreeNode* current = children[idx];
    while (!current->leaf) {
        current = current->children[current->numKeys];
    }
    return current->data[current->numKeys - 1];
}

KeyPair BTreeNode::getSuccessor(int idx) {
    BTreeNode* current = children[idx + 1];
    while (!current->leaf) {
        current = current->children[0];
    }
    return current->data[0];
}

void BTreeNode::fill(int idx) {
    if (idx != 0 && children[idx - 1]->numKeys >= M) {
        borrowFromPrev(idx);
    } else if (idx != numKeys && children[idx + 1]->numKeys >= M) {
        borrowFromNext(idx);
    } else {
        if (idx != numKeys) {
            merge(idx);
        } else {
            merge(idx - 1);
        }
    }
}

void BTreeNode::borrowFromPrev(int idx) {
    BTreeNode* child = children[idx];
    BTreeNode* sibling = children[idx - 1];

    for (int i = child->numKeys - 1; i >= 0; i--) {
        child->data[i + 1] = child->data[i];
    }

    if (!child->leaf) {
        for (int i = child->numKeys; i >= 0; i--) {
            child->children[i + 1] = child->children[i];
        }
        child->children[0] = sibling->children[sibling->numKeys];
    }

    child->data[0] = data[idx - 1];

    data[idx - 1] = sibling->data[sibling->numKeys - 1];
    sibling->numKeys--;
    child->numKeys++;
}

void BTreeNode::borrowFromNext(int idx) {
    BTreeNode* child = children[idx];
    BTreeNode* sibling = children[idx + 1];

    child->data[child->numKeys] = data[idx];

    if (!child->leaf) {
        child->children[child->numKeys + 1] = sibling->children[0];
    }

    data[idx] = sibling->data[0];

    for (int i = 1; i < sibling->numKeys; i++) {
        sibling->data[i - 1] = sibling->data[i];
    }

    if (!sibling->leaf) {
        for (int i = 1; i <= sibling->numKeys; i++) {
            sibling->children[i - 1] = sibling->children[i];
        }
    }

    sibling->numKeys--;
    child->numKeys++;
}

void BTreeNode::merge(int idx) {
    BTreeNode* child = children[idx];
    BTreeNode* sibling = children[idx + 1];

    child->data[M - 1] = data[idx];

    for (int i = 0; i < sibling->numKeys; i++) {
        child->data[i + M] = sibling->data[i];
    }

    if (!child->leaf) {
        for (int i = 0; i <= sibling->numKeys; i++) {
            child->children[i + M] = sibling->children[i];
        }
    }

    for (int i = idx + 1; i < numKeys; i++) {
        data[i - 1] = data[i];
    }

    for (int i = idx + 2; i <= numKeys; i++) {
        children[i - 1] = children[i];
    }

    child->numKeys += sibling->numKeys + 1;
    numKeys--;
    delete sibling;
}

BTree::BTree() : root(nullptr) {}

BTree::~BTree() {
    delete root;
}

void BTree::insert(int key1, int key2) {
    KeyPair kp = {key1, key2};
    if (!root) {
        root = new BTreeNode(true);
        root->data[0] = kp;
        root->numKeys = 1;
    } else {
        if (root->numKeys == 2 * BTreeNode::M - 1) {
            BTreeNode* newRoot = new BTreeNode(false);
            newRoot->children[0] = root;
            newRoot->splitChild(0, root);
            int i = (newRoot->data[0] < kp) ? 1 : 0;
            newRoot->children[i]->insertNonFull(kp);
            root = newRoot;
        } else {
            root->insertNonFull(kp);
        }
    }
}

bool BTree::search(int key1, int key2) {
    KeyPair kp = {key1, key2};
    return root && root->search(kp);
}

void BTree::remove(int key1, int key2) {
    KeyPair kp = {key1, key2};
    if (!root) {
        std::cout << "Дерево пусто.\n";
        return;
    }
    root->remove(kp);
    if (root->numKeys == 0) {
        BTreeNode* oldRoot = root;
        root = root->leaf ? nullptr : root->children[0];
        delete oldRoot;
    }
}

void BTree::printTree(BTreeNode* node, int level) {
    if (node) {
        for (int i = 0; i < node->numKeys; i++) {
            if (!node->leaf) {
                printTree(node->children[i], level + 1);
            }
            for (int j = 0; j < level; j++) {
                std::cout << "   ";
            }
            std::cout << "(" << node->data[i].key1 << ", " << node->data[i].key2 << ")\n";
        }
        if (!node->leaf) {
            printTree(node->children[node->numKeys], level + 1);
        }
    }
}

void BTree::print() {
    printTree(root, 0);
    std::cout << std::endl;
}
