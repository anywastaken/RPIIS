#include "Solution.h"
#include <iostream>

Node::Node(std::string s) : data(s), next(nullptr) {}

Solution::Solution() : head(nullptr) {}

void Solution::Take(int n) {
    Node* temp = head;
    if (n <= 0) {
        std::cout << "Error\n";
        return;
    }
    int counter = 1;
    while (temp) {
        if (counter == n) {
            std::cout << temp->data << '\n';
            return;
        }
        else {
            counter++;
            temp = temp->next;
        }
    }
    std::cout << "Error\n";
}

void Solution::setQueue(std::string s) {
    Node* newnode = new Node(s);
    if (!head) {
        head = newnode;
    }
    else {
        Node* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newnode;
    }
}
