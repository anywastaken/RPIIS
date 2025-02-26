#include "set.h"



string ReplaceInnerSet(string &input, map<string, Set> &sets, int &counter){
	regex setRegex(R"(([{<])([^{}<]*?)([}>]))");
	regex setRegex_2(R"(((\{\w*(,\w+)*\})|(\<\w*(,\w+)*\>))(?=,|\}|\>))");
	smatch match, match_2;
	string result = input;

	while (regex_search(result, match, setRegex) && regex_search(result, match_2, setRegex_2)){
		string uniqueName = "_uniq_" + to_string(counter);
		string setType = match[1].str();
		string innerSetContent = match[2].str();

		Set tempSet;
		tempSet.name = uniqueName;
		if (setType == "<") tempSet.oriented = true;
		else tempSet.oriented = false;

		regex elementRegex(R"(\s*,\s*)");
		sregex_token_iterator iter(innerSetContent.begin(), innerSetContent.end(), elementRegex, -1);
		sregex_token_iterator end;

		// Добавляем элементы в структуру
		for (; iter != end; ++iter) {
			string element = iter->str();
			tempSet.elements.push_back(element);
		}

		if (!tempSet.oriented)
			sort(tempSet.elements.begin(), tempSet.elements.end());
		
		string findresult = FindSet(sets, tempSet.elements, tempSet.oriented);
		if (findresult != "")
			result = match.prefix().str() + findresult + match.suffix().str();
		else{
			result = match.prefix().str() + uniqueName + match.suffix().str();
			sets[uniqueName] = tempSet;
			counter++;
		}
	}
	return result;
}


string FindSet(map<string, Set> &sets, vector<string> elements, bool oriented){
	for (const auto& [name, set] : sets){
		if (set.oriented == oriented && set.elements == elements)
			return name;
	}
	return "";
}

Set MakeSet(string &input, map<string, Set> &sets, int &counter){
	string clearinput = ReplaceInnerSet(input, sets, counter);

	regex nameRegex(R"((\w+)=\s*([{<])([^{}<>\s]*)([}>]))");
	smatch match;
	Set setresult;

	if (regex_search(clearinput, match, nameRegex)){
		setresult.name = match[1].str();
		if (match[2].str() == "{")
			setresult.oriented = false;
		else
			setresult.oriented = true;

		
		string elementsStr = match[3].str();
		regex elementRegex(R"(\s*,\s*)");
		sregex_token_iterator iter(elementsStr.begin(), elementsStr.end(), elementRegex, -1);
		sregex_token_iterator end;

		for (; iter != end; ++iter) {
			string element = iter->str();
			setresult.elements.push_back(element);
		}

		if (!setresult.oriented)
			sort(setresult.elements.begin(), setresult.elements.end());

		string findresult = FindSet(sets, setresult.elements, setresult.oriented);
		if (findresult != ""){
			for (auto& [name, set] : sets){
				auto it = find(set.elements.begin(), set.elements.end(), findresult);
				if (it != set.elements.end())
					*it = setresult.name;
			}
		}
	}else {
		throw exception();
	}
	return setresult;
}


bool ReadFile(string file, map<string, Set> &sets){
	ifstream fin;
	fin.open(file);
	string input;

	if (fin.is_open()){
		string temp;
		while (getline(fin, temp))
			input += temp + "\n";
		fin.close();

		istringstream stream(input);
		string line;

		int counter{0};
		while(getline(stream, line)){
			Set newset = MakeSet(line, sets, counter);
			sets[newset.name] = newset;
		}

	} else
		return false;
	
	return true;
}

vector<string> Opertion(Set result, Set set){
	vector<string> temp;
	set_intersection(
		result.elements.begin(), result.elements.end(),
		set.elements.begin(), set.elements.end(),
		back_inserter(temp)
	);
	return temp;
}

void WriteRecursiv(Set set, map<string, Set> &sets, ofstream &fout){
	if (set.oriented) fout << "<";
	else fout << "{";

	for (int i{0}; i < set.elements.size(); i++){
		if (set.elements[i][0] == '_'){

			for(auto& [name, other_set] : sets){
				if (set.elements[i] == name && set.name != set.elements[i]){

					WriteRecursiv(other_set, sets, fout);
					if (i < set.elements.size() - 1 )
						fout << ",";
					break;
				}
			}
			continue;
		}
		fout << set.elements[i];
		if (i < set.elements.size() - 1 )
			fout << ",";
	}

	if (set.oriented) fout << ">";
	else fout << "}";
}

void Write(Set result, map<string, Set> &sets, string file){
	ofstream fout;
  file.pop_back(); file.pop_back(); file.pop_back(); file.pop_back();
	fout.open("../sets/result/RESULT(" + file.substr(14) + ").txt");
	if (fout.is_open()){
		fout << result.name << "=";
		WriteRecursiv(result, sets, fout);
		fout.close();
	}
	else{
		cout << "Ошибка???\n";
	}
}

void Intersection(string file){
	map<string, Set> sets;
	if (!ReadFile(file, sets))
		throw exception();

	Set result;
	result.name = "Result";
	result.oriented = false;

	for (auto& [name, set] : sets){
		if (name[0] != '_'){
			if (result.elements.size() == 0)
				result.elements = set.elements;
			else
				result.elements = Opertion(result, set);
		}
	}

	Write(result, sets, file);
}