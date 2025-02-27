#include <iostream>

#include "queue.h"
int main(){
    queue q;
    q.push(10);
    q.push(12);
    q.push(1);
    q.push(2);
    q.push(3);
    std::cout<<"queue from begin:"<<std::endl;

    q.show_begin();

    std::cout<<std::endl<<q.pop()<<" - first element."<<std::endl;

    std::cout<<std::endl<<"queue from end:"<<std::endl;
    q.show_end();
}