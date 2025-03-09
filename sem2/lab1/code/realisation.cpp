#include "Header.h"

Double_Arr::Double_Arr(int rows, int cols)
{
    this->rows = rows;
    row_size = new int[rows];
    arr = new int* [rows];
    for (int i = 0; i < rows; i++)
    {
        arr[i] = new int[cols];
        row_size[i] = cols;
        for (int j = 0; j < row_size[i]; j++)
        {
            arr[i][j] = 0;
        }
    }
}

Double_Arr:: ~Double_Arr()
{
    for (int i = 0; i < rows; i++)
    {
        delete[] arr[i];
    }

    delete[] arr;
    delete[] row_size;
}

void Double_Arr::Sort()
{
    int n = 0;
    vector<int> temp;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < row_size[i]; j++)
        {
            temp.push_back(arr[i][j]);
        }
    }
 
    for (int i = 0; i < temp.size(); i++)
    {
        for (int j = 0; j < temp.size() - i - 1; j++)
        {
            if (temp[j] > temp[j + 1])
            {
                swap(temp[j], temp[j + 1]);
            }
        }
    }
    
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < row_size[i]; j++)
        {
            arr[i][j] = temp[n];
            n++;
        }
    }
}

void Double_Arr::Insert_Elem(int elem, int row, int col)
{
    if (row < 0 || col < 0 || row >= rows || col > row_size[row])
    {
        cout << "Неверные параметры вставки" << endl;
        return;
    }

    int* newRow = new int[row_size[row] + 1];
    for (int i = 0; i < col; i++)
    {
        newRow[i] = arr[row][i];
    }
    newRow[col] = elem;
    for (int i = col; i < row_size[row]; i++)
    {
        newRow[i + 1] = arr[row][i];
    }
    delete[] arr[row];
    arr[row] = newRow;
    row_size[row]++;
}

void Double_Arr::Search_Elem(int elem)
{
    bool check_elem = false;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < row_size[i]; j++)
        {
            if (arr[i][j] == elem)
            {
                cout << "Элемент находится на позиции (" << i << ", " << j << ")" << endl;
                check_elem = true;
            }
        }
    }

    if (!check_elem)
    {
        cout << "Елемент не найден";
    }
}

void Double_Arr::View_Arr()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < row_size[i]; j++)
        {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}

bool Double_Arr::Sort_Check()
{
    vector<int> temp;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < row_size[i]; j++)
        {
            temp.push_back(arr[i][j]);
        }
    }

    for (int i = 0; i < temp.size() - 1; i++)
    {
        if (temp[i] > temp[i + 1])
            return false;
    }

    return true;
}

Double_Arr Double_Arr::Union(Double_Arr& second_arr)
{
    vector<vector<int>> resultVec;
    for (int i = 0; i < rows; i++)
    {
        resultVec.push_back(vector<int>(arr[i], arr[i] + row_size[i]));
    }

    for (int i = 0; i < second_arr.rows; i++)
    {
        resultVec.push_back(vector<int>(second_arr.arr[i], second_arr.arr[i] + second_arr.row_size[i]));
    }
    
    int new_rows = resultVec.size();
    Double_Arr result(new_rows, 0);

    for (int i = 0; i < new_rows; i++)
    {
        result.row_size[i] = resultVec[i].size();
        result.arr[i] = new int[result.row_size[i]];
        copy(resultVec[i].begin(), resultVec[i].end(), result.arr[i]);
    }

    return result;
}


Double_Arr Double_Arr::Intersection(Double_Arr& second_arr)
{
    vector<vector<int>> resultVec;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < second_arr.rows; j++)
        {
            if (row_size[i] == second_arr.row_size[j] && equal(arr[i], arr[i] + row_size[i], second_arr.arr[j])) 
            {
                resultVec.push_back(vector<int>(arr[i], arr[i] + row_size[i]));
                break;
            }
        }
    }

    int newRows = resultVec.size();
    Double_Arr result(newRows, 0);
    for (int i = 0; i < newRows; i++)
    {
        result.row_size[i] = resultVec[i].size();
        result.arr[i] = new int[result.row_size[i]];
        copy(resultVec[i].begin(), resultVec[i].end(), result.arr[i]);
    }
    
    return result;
}

void Double_Arr::Input_Arr()
{
    int new_rows, new_cols;
    cout << "Введите размер массива: ";
    cin >> new_rows >> new_cols;

    for (int i = 0; i < rows; i++) {
        delete[] arr[i];
    }
    delete[] arr;
    delete[] row_size;

    rows = new_rows;
    row_size = new int[rows];
    arr = new int* [rows];
    cout << "Введите элементы массива: ";
    for (int i = 0; i < rows; i++)
    {
        arr[i] = new int[new_cols];
        row_size[i] = new_cols;
        for (int j = 0; j < new_cols; j++)
        {
            cin >> arr[i][j];
        }
    }
}

void Double_Arr::Read_File(const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        int new_rows, new_cols;
        file >> new_rows >> new_cols;

        for (int i = 0; i < rows; i++) {
            delete[] arr[i];
        }
        delete[] arr;
        delete[] row_size;

        arr = new int* [new_rows];
        row_size = new int[new_rows];

        for (int i = 0; i < new_rows; i++) {
            arr[i] = new int[new_cols];
            row_size[i] = new_cols;
        }

        rows = new_rows;

        for (int i = 0; i < new_rows; i++) {
            for (int j = 0; j < new_cols; j++) {
                file >> arr[i][j];
            }
        }
        file.close();
    }
    else {
        cout << "Не удалось открыть файл";
    }
}