#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include <string>

class Node {
public:
    std::string data;
    Node* next;
    Node(std::string s);
};

class Solution {
public:
    Solution();
    void Take(int n);
    void setQueue(std::string s);

private:
    Node* head;
};

#endif // SOLUTION_HPP
