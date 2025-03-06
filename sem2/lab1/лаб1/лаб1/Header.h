#pragma once
#include <vector>
#include <string>
using namespace std;
class suffix_array {
public:
	suffix_array(string str); 
	void view();
	string LCP(); 
	string SCS(); 
private:
	vector<string> suffixes;
	vector<string> shifts;
};
