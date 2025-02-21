/*******************************************

Название: Булеан
Разработчик: Шумилов Артем Андреевич
Дата: 20.02.2025
Описание: Программа считывает из текстового
файла строку, которая содержит множество,
заданное перечислением. После этого
вычисляется булеан этого множество. Каждое 
множество булеана обладает всеми методами множества

********************************************/

#include <iostream>
#include <fstream>
#include "Set.hpp"

using namespace std;
 
int main()
{
    ifstream fromFile("input.txt");
    string str;
    if(fromFile.is_open()){ //считывание с файла
        getline(fromFile, str);
        fromFile.close();
        std::cout << "File was successfully read!" << std::endl;
    }
    else cout << "Problems with reading from file!" << endl;

    Set mySet(str);
    mySet.displayBoolean();
    vector< Set> boolean = mySet.getBoolean();
    for(auto set : boolean){
        set.displayBoolean();
    }
    mySet.addElement("p");
    mySet.displayBoolean();
    boolean[0].displayBoolean();
    return 0;
}