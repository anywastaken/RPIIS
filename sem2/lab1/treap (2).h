#ifndef TREAP_H
#define TREAP_H

struct item {
    int key, prior;
    item* l, * r;
    item() { }
    item(int key, int prior) : key(key), prior(prior), l(nullptr), r(nullptr) { }
};
typedef item* pitem;

class Treap {
public:
    Treap();
    ~Treap();

    void insert(int key);
    pitem find(int key);
    void remove(int key);
    void buildFromArray(int arr[], int size);
    Treap* merge(Treap* other);
    Treap* intersect(Treap* other);
    pitem root;

private:
    void split(pitem t, int key, pitem& l, pitem& r);
    void insert(pitem& t, pitem it);
    void merge(pitem& t, pitem l, pitem r);
    void erase(pitem& t, int key);
    pitem unite(pitem l, pitem r);
    void destroy(pitem node);
    pitem intersect(pitem t1, pitem t2);
    pitem mergeNodes(pitem l, pitem r); // Добавлено объявление новой функции
};

#endif