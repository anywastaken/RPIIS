#include <iostream>
using namespace std;

struct Node
{
    int value;
    Node *next;
    Node(int _value):value(_value),next(nullptr){};
};

struct List
{
    Node *first;
    Node *last;
    int size;
    List():first(nullptr),last(nullptr),size(0){};
    ~List()
    {
        clear();
    }
    

    bool is_empty();

    int Get_size();

    void push_b(int _value);

    void Print();

    bool find(int _value);

    void Remove_first();

    void Remove_last();

    void Remove(int _val);

    void clear();

    List& operator=(List b);

    Node *operator[](int index);

    void Sort();  

    List intersection_list(Node *current2);

    List union_list(Node *current2); 
};

