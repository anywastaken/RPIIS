#pragma once
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Graph {

    int n;
    int m;
    vector<vector<int>> matrix;


    void InputMatrix();
    void PrintMatrix();
    void AddVertex();
    void DelVertex();
    void AddArc();
    void DelArc();
    void BFS();
    void ShowMenu();
    void prog();
};
