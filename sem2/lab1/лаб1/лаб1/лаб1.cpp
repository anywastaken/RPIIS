#include "Header.h"
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

void read_from_file(const string& filename) {
    ifstream File(filename);
    if (!File) {
        cerr << "Error!!!!!!" << endl;
        return;
    }

    string word;
    while (File >> word) {
        cout << "Test word: " << word << endl;
        suffix_array sf = suffix_array(word);
        sf.view();

        cout << "The largest common prefix of two substrings: " << sf.LCP() << endl;
        cout << "The smallest cyclic shift: " << sf.SCS() << endl;
        cout << "-----------------------------" << endl;
    }

    File.close();
}

int main() {
	const string filename = "words.txt";
	read_from_file(filename);

    cout << "Enter the word: " << endl;
    string str;
    cin >> str;
    suffix_array sf = suffix_array(str);
    sf.view();

    cout << "The largest common prefix of two substrings:" << endl;
    cout << sf.LCP() << endl;
    cout << "The smallest cyclic shift:" << endl;
    cout << sf.SCS() << endl;

    return 0;
}