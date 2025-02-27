#ifndef PIOVIS_LABA2
#define PIOVIS_LABA2

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <stack>
const char skoba1 = '{';
const char skoba2 = '}';
const char skoba3 = '<';
const char skoba4 = '>';
using namespace std;
class Union {
private:
    vector<string> test;

public:

    void shitivanie() {
        cout << "Введите размерность множества" << endl;
        int si;
        cin >> si;
        cin.ignore();
        for (int i = 0; i < si; i++) {
            string stroka;
            getline(cin, stroka);
            if (!stroka.empty()) {
                test.push_back(stroka);
            }
        }
    }

    void set_of_vector(vector <string> testi) {
        test = testi;
    }

    void print() {
        for (const auto& el : test) {
            cout << el << ' ';
        }
    }
    vector<string>& get_vector() {
        return test;
    }
    string first_stroka_in_vector() {
        return test[0];
    }

    vector <string>& set_vector(vector<string> first) {
        test = first;
        return test;
    }

};



bool is_set(const string& str) {
    return str[0] == '{' && str[str.length() - 1] == '}';
}
bool is_kortezh(const string& str) {
    return str[0] == '<' && str[str.length() - 1] == '>';
}

bool compare_strings(const string& a, const string& b) {
    int i = 0;
    int j = 0;

    while (i < a.length() && j < b.length()) {
        if (a[i] < b[j]) return true;
        if (a[i] > b[j]) return false;
        i++; j++;
    }
    return a.length() < b.length();
}



void bubble_sort(vector<string>& elements) {
    for (size_t i = 0; i < elements.size(); i++) {
        for (size_t j = 0; j < elements.size() - 1 - i; j++) {
            if (!compare_strings(elements[j], elements[j + 1])) {
                string temp = elements[j];
                elements[j] = elements[j + 1];
                elements[j + 1] = temp;
            }
        }
    }
}

void remove_duplicates(vector<string>& elements) {
    if (elements.empty()) return;
    vector <string> unique;
    for (int i = 0; i < elements.size(); i++) {
        bool flag = false;
        for (int j = 0; j < unique.size(); j++) {
            if (elements[i] == unique[j]) {
                flag = true;
                break;
            }
        }
        if (!flag) {
            unique.push_back(elements[i]);
        }
    }
    elements = unique;
}


vector<string> get_elements(string& set) {
    vector<string> elements;
    string current;
    int bracket_count = 0;
    int bracket_count_treug = 0;

    for (int i = 1; i < set.length() - 1; i++) {
        char c = set[i];

        if (c == '{') {
            bracket_count++;
            current += c;
        }
        else if (c == '}') {
            bracket_count--;
            current += c;
            if (bracket_count == 0 && bracket_count_treug == 0) {
                elements.push_back(current);
                current.clear();
            }
        }
        else if (c == '<') {
            bracket_count_treug++;
            current += c;
        }
        else if (c == '>') {
            bracket_count_treug--;
            current += c;
            if (bracket_count == 0 && bracket_count_treug == 0) {
                elements.push_back(current);
                current.clear();
            }
        }
        else if ((c == ','||c==' ') && bracket_count == 0 && bracket_count_treug == 0) {
            if (!current.empty()){
                elements.push_back(current);
            current.clear();
            }
        }
        else {
            current += c;
        }
    }
    
    if (!current.empty()) {
        elements.push_back(current);
    }

    return elements;
}
string sort_set(string& str) {
    if (is_kortezh(str)) {
        vector<string> elements = get_elements(str);
        for (auto& element : elements) {
            if (is_set(element) || is_kortezh(element)) {
                element = sort_set(element);
            }
        }
        string result = "<";
        for (size_t i = 0; i < elements.size(); i++) {
            if (i > 0) result += ",";
            result += elements[i];
        }
        result += ">";
        return result;
    }

    if (is_set(str)) {
        vector<string> elements = get_elements(str);
        for (auto& element : elements) {
            if (is_set(element) || is_kortezh(element)) {
                element = sort_set(element);
            }
        }
        bubble_sort(elements);
        remove_duplicates(elements);
        string result = "{";
        for (size_t i = 0; i < elements.size(); i++) {
            if (i > 0) result += ",";
            result += elements[i];
        }
        result += "}";
        return result;
    }

    return str;
}
void peresechenie(vector <string> tes, vector<string>& result) {
    vector <string> temp;
    for (auto& el : tes) {
        bool flag = false;
        for (auto& pers : result) {
            if (el == pers) {
                flag = true;
                break;
            }
        }
        if (flag) {
            temp.push_back(el);
        }
    }
    result.clear();
    result = temp;
}
void main_peresechenie(vector <Union>& testi, vector<string>& result) {
    vector <string>temp;
    for (int i = 1; i < testi.size(); i++) {
        peresechenie(testi[i].get_vector(), result);
    }
}

bool checking_pravilnost_stroki(string stroka) {
    stack<char> stack1;
    for (int i = 0; i < stroka.length(); i++) {
        if (stroka[i] == skoba1) {
            stack1.push(skoba1);
        }
        else if (stroka[i] == skoba2) {
            if (stack1.empty()) {
                return false;
            }
            else if (stack1.top() == skoba1) {
                stack1.pop();
            }
            else return false;
        }
        else if (stroka[i] == skoba3) {
            stack1.push(skoba3);
        }
        else if (stroka[i] == skoba4) {
            if (stack1.empty()) {
                return false;
            }
            else if (stack1.top() == skoba3) {
                stack1.pop();
            }
            else return false;
        }
    }
    if (stack1.empty()) return true;
    else return false;
}



void shitivanie_file(vector <Union> &us) {
    ifstream file;
    file.open("input.txt");
    if (file.is_open()) {
        string stroka;
        getline(file, stroka);
        int size_of_union = stoi(stroka);
        us.resize(size_of_union);
        for (int i = 0; i < size_of_union; i++) {
            string stroka2;
            getline(file, stroka2);
          
            vector <string> legend;
            legend.clear();
            int size_of_mn = stoi(stroka2);
            for (int j = 0; j < size_of_mn; j++) {
                string res;
                getline(file, res);
                legend.push_back(res);
            }
            us[i].set_of_vector(legend);
            
        }
        file.close();
        
    }
    else {
        cout << "Файл не открыт!!!";
        return;
    }
}



#endif
