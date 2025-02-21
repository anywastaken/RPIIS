#include "Set.hpp"
#include <cmath>
#include <utility>

Set::Set(){
    std::cout << "Empty set was created!" << std::endl;
}

Set::Set(std::string str){
    if(extractSet(str) && isCorrect(str)){
        str.erase(0, 1);
        str.erase(str.size() - 1, 1);
        divideWords(str);
    }
    else{
        std::cout << "Incorrect input!" << std::endl;
        Set();
    }
}

Set::Set(std::vector< std::string> elements)
:setElements(std::move(elements)){
}

bool Set::extractSet(std::string& str){  //Извлечение множества из считанной строки 
    for(size_t i = 0; i < str.size(); i++){
        if(str[i] == '{'){
            str.erase(0, i);
            return true;
        }
    }
    return false; //Индикатор возможности извлечения множества
}

void Set::divideWords(std::string str){ //Разделение строки на слова
    size_t i = 0;
    int openPar = 0;
    while(!str.empty()){
        if(str[i] == ',' && openPar == 0){ //слова разделяются запятыми
            setElements.push_back(str.substr(0, i));
            str.erase(0, i + 1);
            i = 0;
        }
        else i++;

        if(str[i] == '{')
            openPar++;
        else if(str[i] == '}')
            openPar--;
    }
}

bool Set::isCorrect(std::string str){ //Проверка на корректность введенных данных
    if(str.size() < 2 || str[str.size() - 1] != '}')
        return false;

    int openPar = 0;
    for(size_t i = 0; i < str.size(); i++){
        if(str[i] == '{'){
            openPar++;
            continue;
        }

        if(str[i] == '}' && openPar == 0){
            return false;
        }
        else if(str[i] == '}'){
            openPar--;
        }
    }

    if(openPar == 0){
        return true;
    }
    else return false;
}

void Set::addElement(std::string element){ //Добавление нового элемента во множество
    setElements.push_back(element);
    std::cout << "New element was successfully added!" << std::endl;
}

std::vector< std::string> Set::getSubSet(int n){ //Извлечение подмножества из начального множества
    int i = 0;
    std::vector< std::string> temp;
    while (n){
        if (n & 1)
            temp.push_back(setElements[i]);
        i++;
        n >>= 1;
    }
    return temp; //Возвращает извлеченное подмножество
}

std::vector< Set> Set::getBoolean(){ //Получение булеана
    int n = pow(2, setElements.size());
    std::vector< Set> boolean;
    for(int i = 0; i < n; i++){
        Set temp(getSubSet(i));
        boolean.push_back(temp);
    }
    return boolean; //Возвращает булеан
}

void Set::displaySet(){ //Вывод множества в консоль
    std::cout << "{";
    for(int i = 0; i < setElements.size(); i++){
        std::cout << setElements[i];
        if(i != setElements.size() - 1){
            std::cout << ",";
        }
    }
    std::cout << "}";
}

void Set::displayBoolean(){ //Вывод булеана в консоль
    std::vector< Set> boolean;
    boolean = getBoolean();
    std::cout << "Boolean: {";
    for(int i = 0; i < boolean.size(); i++){
        boolean[i].displaySet();
        if(i != boolean.size() - 1){
            std::cout << ',';
        }
    }
    std::cout << "}" << std::endl;
}