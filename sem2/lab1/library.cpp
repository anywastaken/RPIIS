#include "../include/library.h"

namespace YoungDiagram {

    bool YoungTable::CheckDublicate(int x, YoungDiagram::YoungTable &P) {
        for (size_t i = 0; i < P.Table.size(); ++i) {
            for (size_t j = 0; j < P.Table[i].size(); ++j) {
                if (x == P.Table[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }

    bool YoungTable::CheckTable(YoungDiagram::YoungTable &P) {
        //Check form of the table
        for (int i = 1; i < P.Table.size(); i++) {
            if(P.Table[i-1].size() < P.Table[i].size()){
                return false;
            }
        }
        // Check for unique elements
        for (size_t i = 0; i < P.Table.size(); ++i) {
            for (size_t j = 0; j < P.Table[i].size(); ++j) {
                for (size_t k = i; k < P.Table.size(); ++k) {
                    for (size_t l = (k == i ? j + 1 : 0); l < P.Table[k].size(); ++l) {
                        if (P.Table[i][j] == P.Table[k][l]) {
                            //std::cout << "Error, table can't contain same numbers";
                            return false;
                        }
                    }
                }
            }
        }

        // Check sort
        for (size_t i = 0; i < P.Table.size(); ++i) {
            for (size_t j = 0; j < P.Table[i].size(); ++j) {
                // Line check: element must be less than the next one in the line
                if (j < P.Table[i].size() - 1 && P.Table[i][j] >= P.Table[i][j + 1]) {
                    //std::cout << "Error, lines must be sorted in ascending order.\n";
                    return false;
                }

                // Column check: element must be less than the next one in the column
                if (i < P.Table.size() - 1 && j < P.Table[i + 1].size() && P.Table[i][j] >= P.Table[i + 1][j]) {
                    //std::cout << "Error, columns must be sorted in ascending order.\n";
                    return false;
                }
            }
        }
        return true;
    }

    bool YoungTable::CheckExtremePositions(int s, int t, YoungDiagram::YoungTable &P) {
        if (P.Table[s].size() - 1 == t && (P.Table.size() - 1 == s || P.Table[s + 1].size() - 1 < t)) {
            return true;
        } else {
            return false;
        }
    }

    ResultCode YoungTable::AddToTable(YoungDiagram::YoungTable &P, int x) {
        if (CheckDublicate(x, P) == false) {
            //std::cout << "Error, Element must not be repeated with existing ones.\n";
            return ResultCode::DublicateError;
        }
        if(CheckTable(P) == false) {
            //std::cout<<"Error, this is not a Young table.\n";
            return ResultCode::WrongTableError;
        }
        for (int i = 0; i < P.Table.size(); i++) {
            if (P.Table[i].empty() == true) {
                P.Table[i].push_back(x);
                return ResultCode::Success;
                break;
            }
            bool isGreater = true;
            for (int j = 0; j < P.Table[i].size(); j++) {
                if (x < P.Table[i][j]) {
                    std::swap(x, P.Table[i][j]);
                    isGreater = false;
                    if (i == P.Table.size() - 1) {
                        P.Table.push_back({});
                    }
                    break;
                }
            }
            if (isGreater == true) {
                P.Table[i].push_back(x);
                return ResultCode::Success;
                break;
            }
        }
        if (P.Table.size() == 0) {
            P.Table.push_back({x});
            return ResultCode::Success;
        }

    }

    ResultCode YoungTable::DeleteFromTable(YoungDiagram::YoungTable &P, int s, int t) {
        s--;
        t--;
        if (CheckExtremePositions(s, t, P) == false) {
            //std::cout << "Error, You can delete only from extreme positions\n";
            return ResultCode::WrongPositionToDeleteError;
        }
        if(CheckTable(P) == false) {
            //std::cout<<"Error, this is not a Young table.\n";
            return ResultCode::WrongTableError;
        }
        int x = P.Table[s][t];
        P.Table[s].erase(P.Table[s].begin() + t);
        if(P.Table[s].empty() == true){
            P.Table.erase(P.Table.begin() + s);
        }
        for (int i = s - 1; i > -1; i--) {
            bool swapped = false;
            for (int j = 0; j < P.Table[i].size() - 1; j++) {
                if (x > P.Table[i][j] && x < P.Table[i][j + 1]) {
                    swapped = true;
                    std::swap(x, P.Table[i][j]);
                    break;
                }
            }
            if (swapped == false) {
                std::swap(x, P.Table[i][P.Table[i].size() - 1]);
            }
        }
        return ResultCode::Success;
    }
}
