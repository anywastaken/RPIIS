#include "queue.h"
#include "Node.h"
#include <iostream>

queue::queue(){
    first = nullptr;
    last = nullptr;
}
queue::~queue(){
    while(first!=nullptr){
        pop();
    }
}
void queue::show_begin(){
    Node* temp = first;
    while(temp != nullptr){
        std::cout<<temp->value<<std::endl;
        temp = temp->next;
        
    }
}

void queue::show_end(){
    Node* temp = last;
    while(temp !=nullptr){
        
        std::cout<<temp->value<<std::endl;
        if(temp == first) 
            break;
        temp = temp->prev;
    }
}

void queue::push(int value){
    Node* temp= new Node(value);
    if(first == nullptr){
        first = temp;
        last = first;
    }
    else{
        Node* ptr = last;
        last->next = temp;
        last = temp;
        last->prev = ptr;
    }
    
}
int queue::peek(){
    return first->value;
}
int queue::pop(){
    Node* temp = first;
    if(first==nullptr){
        throw "queue is empty";
    }
    int result = first->value;
    first = first->next;
    delete temp;
    return result;
}


