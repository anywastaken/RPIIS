#include "Header.h"
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;


string suffix_array::LCP() {
    string biggest; 
    string lcp;     
   
    for (int i = 1; i < suffixes.size(); i++) {
        lcp.clear(); 
       
        for (int j = 0; j < min(suffixes[i].size(), suffixes[i - 1].size()); j++) {
            if (suffixes[i - 1][j] == suffixes[i][j]) {
                lcp += suffixes[i][j];
            }
            else {
                break; 
            }
        }
        if (i == 1) biggest = lcp; 
        if (i > 1 && biggest.size() < lcp.size()) biggest = lcp;
    }
    return biggest;
}

void suffix_array::view() {
    for (const auto& str : this->suffixes) {
        cout << str << endl;
    }
}

suffix_array::suffix_array(string str) {
    for (int i = 0; i < str.size(); i++) {
        this->suffixes.push_back(string(str.begin() + i, str.end())); 
        this->shifts.push_back(string(str.begin() + i, str.end()) + string(str.begin(), str.begin() + i));

    }
    sort(suffixes.begin(), suffixes.end()); 
    sort(shifts.begin(), shifts.end());
}

string suffix_array::SCS() {
    return shifts.back();
}