#ifndef MNOJESTVO_H
#define MNOJESTVO_H

#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <algorithm>
#include <stdexcept>

// регулярное выражение для всего файла.
#define FORMA_1 "(\\w\\w*=((\\{\\w*(,\\w+)*\\})|(\\<\\w*(,\\w+)*\\>))\n)+"

// регулярное выражение для множеств внутри другого множества.
#define FORMA_2 "((\\{\\w*(,\\w+)*\\})|(\\<\\w*(,\\w+)*\\>))(?=,|\\}|\\>)"

using namespace std;

struct Set{
    string name;
    vector<string> elements;
    bool oriented;
};


string ReplaceInnerSet(string &input, map<string, Set> &sets, int &counter);
string FindSet(map<string, Set> &sets, vector<string> elements, bool oriented);
Set MakeSet(string &input, map<string, Set> &sets, int &counter);
bool ReadFile(string file, map<string, Set> &sets);
void Intersection(string file);
void Write(Set result, map<string, Set> &sets, string file);
void WriteRecursiv(Set set, map<string, Set> &sets, ofstream &fout);
vector<string> Opertion(Set result, Set set);


#endif
