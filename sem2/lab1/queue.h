#pragma once 
#include "Node.h"
struct queue
{
    public:
    queue();
    ~queue();
    void push(int value);
    int pop();
    int peek();
    void show_begin();
    void show_end();
    private:
    Node* first;
    Node* last;
};
