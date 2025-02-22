#include <iostream>
#include "stack.h"

using namespace std;

int main() {
    stack *a = allocate_stack();
    while(true){
        cout << "1) Добавить элемент в стек \n2) Взять элемент из стека \n3) Заверишить программу";
        int type;
        cin >> type;
        if(type == 1){
            int x;
            cin >> x;
            push(x, a);
        }
        else if(type == 2){
            if(isempty(a)){
                cout << "В стеке нет элементов\n";
            }
            else{
                cout << '\n' << pop(a) << '\n' << '\n';
            }
        }
        else
            break;
    }
    del_stack(a);
}
