#ifndef SET_HPP
#define SET_HPP

#include <iostream>
#include <vector>

class Set{
    private:
        std::vector< std::string> setElements; //хранилище элементов множества
        bool isCorrect(std::string str);
        void divideWords(std::string str);
        bool extractSet(std::string& str);
        std::vector< std::string> getSubSet(int n);
        void displaySet();
    public:
        Set();
        explicit Set(std::string str);
        explicit Set(std::vector< std::string> elements);
        void addElement(std::string element);
        std::vector< Set> getBoolean();
        void displayBoolean();
};

#endif


