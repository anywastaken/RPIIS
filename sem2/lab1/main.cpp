
#include "spisok.h"
#include <iostream>
using namespace std;

int main()
{
    List a;
    a.push_b(1);
    a.push_b(1);
    a.push_b(1);
    a.push_b(2);
    a.push_b(1);
    List b;
    b.push_b(2);
    b.push_b(1);
    b.push_b(1);
    List result;List result1;
    result=a.intersection_list(b.first);
    result.Print();
    result1=a.union_list(b.first);
    result1.Print();
    return 0;
}