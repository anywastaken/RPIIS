#ifndef GTEST_LIBRARY_H
#define GTEST_LIBRARY_H

#include <iostream>
#include <vector>
#include <string>

namespace YoungDiagram {
    enum class ResultCode
    {
        Success,
        DublicateError,
        WrongTableError,
        WrongPositionToDeleteError
    };
    struct YoungTable {
        std::vector <std::vector <int> > Table;

        bool CheckDublicate(int x, YoungDiagram::YoungTable& P);
        bool CheckTable(YoungDiagram::YoungTable& P);
        bool CheckExtremePositions(int s, int t, YoungDiagram::YoungTable& P);
        ResultCode AddToTable(YoungDiagram::YoungTable &P, int x);
        ResultCode DeleteFromTable(YoungDiagram::YoungTable &P, int s, int t);
    };
}

#endif //GTEST_LIBRARY_H
