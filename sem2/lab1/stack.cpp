#include "stack.h"
#include <iostream>

#define MAXN 1000

struct stack{
    int sz = 0;
    int val[MAXN];
};

stack * allocate_stack()
{
    return new stack;
}

void push(int x, stack* s){
    s->val[s->sz++] = x;
}

int pop(stack *s)
{
    return s->val[--s->sz];
}

bool isempty(stack *s){
    return s->sz==0;
}

void del_stack(stack *s){
    delete s;
}