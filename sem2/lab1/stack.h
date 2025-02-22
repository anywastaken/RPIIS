#ifndef STACK_H
#define STACK_H

struct stack;

stack * allocate_stack();

void del_stack(stack*);

void push(int, stack*);

int pop(stack*);

bool isempty(stack*);

#endif