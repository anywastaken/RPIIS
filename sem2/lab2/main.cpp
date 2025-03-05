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
#include "Set_lib/Set.hpp"

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

    string line(120, '-');
    Set mySet(str);
    mySet.displayBoolean();
    cout << line << endl;

    vector< Set> boolean = mySet.getBoolean();
    for(auto set : boolean){
        set.displayBoolean();
    }
    cout << line << endl;

    cout << "Boolean after adding" << endl;
    mySet.addElement("{");
    mySet.displayBoolean();

    cout << line << endl;
    string str2;
    cout << "Enter the string: ";
    getline(cin, str2);
    Set newSet(str2);
    newSet.displayBoolean();
    return 0;
}