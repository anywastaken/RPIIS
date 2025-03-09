#ifndef DOUBLE_ARR
#define DOUBLE_ARR


#include <fstream>
#include<iostream>
#include <vector>
using namespace std;

class Double_Arr
{
private:
	int rows;
	int* row_size;
	int** arr;
public:
	Double_Arr(int rows, int cols);
	~Double_Arr();
	void Sort();
	void Insert_Elem(int elem, int row, int colum);
	void Search_Elem(int elem);
	void View_Arr();
	void Input_Arr();
	void Read_File(const string& filename);
	bool Sort_Check();
	Double_Arr Union(Double_Arr& second_arr);
	Double_Arr Intersection(Double_Arr& second_arr);
};
#endif