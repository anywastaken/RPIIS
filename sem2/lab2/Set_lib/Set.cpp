#include "Set.hpp"
#include <cmath>
#include <stack>

Set::Set(){
    std::cout << "Empty set was created!" << std::endl;
}

Set::Set(std::string str){
    if(extractSet(str) && isCorrect(str)){
        str.erase(0, 1);
        str.erase(str.size() - 1, 1);
        if(str.size() != 0)
            divideStr(str);
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
        if(str[i] == '{' || str[i] == '<'){
            str.erase(0, i);
            return true;
        }
    }
    return false; //Индикатор возможности извлечения множества
}

void Set::divideStr(std::string str){ //Разделение строки на слова
    size_t i = 0;
    int openPar = 0;
    int openArrow = 0;

    while(i < str.size()){
        if((openPar == 0 && openArrow == 0) && str[i] == ','){ //слова разделяются запятыми
            setElements.push_back(str.substr(0, i));
            str.erase(0, i + 1);
            i = 0;
        }

        if(str[i] == '{')
            openPar++;
        else if(str[i] == '}')
            openPar--;

        if(str[i] == '<')
            openArrow++;
        else if(str[i] == '>'){
            openArrow--;
        }
            
        i++;
    }
    setElements.push_back(str.substr(0, i));
}

bool Set::isCorrectBrackets(std::string str){
    char last = str[str.size() - 1];
    char first = str[0];
    if(first != '{' && first != '<')
        return false;
    else if(first == '{' && last != '}')
        return false;
    else if(first == '<' && last != '>')
        return false;

    std::stack<char> stack;
    for(int i = 0; i < str.size(); i++){
        if(i != 0 && stack.empty())
            return false;

        if(str[i] == '{' || str[i] == '<')
            stack.push(str[i]);
        else if(str[i] == '}'){
            if(stack.empty())
                return false;
            else if(stack.top() == '{')
                stack.pop();
            else return false;
        }
        else if(str[i] == '>'){
            if(stack.top() == '<')
                stack.pop();
            else return false;
        }
    }
    if(stack.empty())
        return true;
    else return false;
}

bool Set::isCorrect(std::string str){ //Проверка на корректность введенных данных
    for(int i = 0; i < str.size(); i++){
        if(str[i] >= 'A' && str[i] <= 'Z')
            continue;
        if(str[i] >= 'a' && str[i] <= 'z')
            continue;
        if(str[i] >= '0' && str[i] <= '9')
            continue;
        if(str[i] == '{' || str[i] == '}')
            continue;
        if(str[i] == '<' || str[i] == '>')
            continue;
        if(str[i] == ','){
            if(str[i + 1] != '}' && str[i - 1] != '{' && str[i - 1] != '<' && str[i + 1] != '>')
                continue;
        }
        return false;
    }
    if(!isCorrectBrackets(str))
        return false;

    return true;
}

void Set::addElement(std::string element){ //Добавление нового элемента во множество
    if(isCorrect(element)){
        setElements.push_back(element);
        std::cout << "New element was successfully added!" << std::endl;
    }
    else std::cout << "Incorrect element!" << std::endl;
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