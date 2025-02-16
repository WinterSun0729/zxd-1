//
// Created by Dong on 2022/10/7.
//

#ifndef INC_2_1_MYCLASS1_H
#define INC_2_1_MYCLASS1_H

#endif //INC_2_1_MYCLASS1_H
#include "std_lib_facilities.h"
#include <set>

class Matrix_Opa{
    double** A;
    int Line;
    int Row;
    vector<double> b;
public:
    Matrix_Opa(int line, int row, set<string>& var_sum, vector<vector<pair<double,string>>>& mat_be, vector<double> &B);
    void test_show();
    int Cauculate(vector<double>& solve_x);

    ~Matrix_Opa(){
        for (int i = 0; i < Line; ++i) {
            delete [] A[i];
        }
        delete [] A;
    }
};