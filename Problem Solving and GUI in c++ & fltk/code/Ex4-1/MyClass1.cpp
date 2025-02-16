//
// Created by Dong on 2022/10/7.
//
#include "std_lib_facilities.h"
#include "MyClass1.h"

Matrix_Opa::Matrix_Opa(int line, int row, set<string>& var_sum, vector<vector<pair<double,string>>>& mat_be, vector<double> &B){
    b = B;
    Line = line;
    Row = row;
    A = new double* [line];
    for(int i = 0; i < line; i++){
        A[i] = new double[row];
    }
    for (int i = 0; i < line; ++i) {
        for (int j = 0; j < row; ++j) {
            A[i][j] = 0;
        }
    }
    for (int i = 0; i < line; ++i) {
        int j = 0;
        for(set<string>::iterator vt = var_sum.begin(); vt != var_sum.end(); vt++){
            for(vector<pair<double,string>>::iterator t = mat_be[i].begin(); t != mat_be[i].end(); t++){
                if(*vt == t->second){
                    A[i][j] = t->first;
                }
            }
            j++;
        }
    }
};

int Matrix_Opa::Cauculate(vector<double>& solve_x) {
    for (int k = 0; k < Row && k < Line; ++k) {
        //交换非零行和零主元所在行
        if (A[k][k] == 0) {
            for (int m1 = k + 1; m1 < Line; m1++) {
                if (A[m1][k] != 0) {
                    double tmp;
                    for (int m2 = 0; m2 < Row; m2++) {
                        tmp = A[k][m2];
                        A[k][m2] = A[m1][m2];
                        A[m1][m2] = tmp;
                    }
                    tmp = b[k];
                    b[k] = b[m1];
                    b[m1] = tmp;
                }
            }
        }
        for (int i = k + 1; i < Line; ++i) {
            double temp = A[i][k]/A[k][k];
            for (int j = k; j < Row; ++j) {
                A[i][j] = A[i][j] - temp*A[k][j];
            }
            b[i] = b[i] - temp * b[k];
        }
    }
    for (int i = 0; i < Line && i < Row; ++i) {
        try {
            if(A[i][i] == 0 && b[i] != 0)throw 1;
            if(i >= 1 && A[i][i-1] != 0)throw 1;
            if(Line > Row)throw 1;
            if(Line < Row)throw 2;
            if(A[i][i] == 0 && b[i] == 0)throw 2;
        }
        catch (int err) {
            return err;
        }
    }
    double* x= new double[Row+1]{0};
    x[Row-1] = b[Line-1]/A[Line-1][Row-1];
    if(Row >= 2){
        for(int i = Row - 2; i >= 0; --i){
            double sum_tmp = 0;
            for (int j = i + 1; j < Row; ++j) {
                sum_tmp += A[i][j]*x[j];
            }
            x[i] = (b[i] - sum_tmp)/A[i][i];
        }
    }
    for(int i = 0; i < Row; i++){
        solve_x.push_back(x[i]);
    }
    return 0;
}

void Matrix_Opa::test_show(){
    for (int i = 0; i < Line; ++i) {
        for (int j = 0; j < Row; ++j) {
            cout << A[i][j] << ' ';
        }
        cout << endl;
    }
    for(auto& t:b){
        cout << t << ' ';
    }
    cout << endl;
}