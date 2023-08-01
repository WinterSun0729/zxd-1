//
// Created by Dong on 2022/10/6.
//
#include <iostream>
#include "Polynomial.h"
#include "cmath"
using namespace std;
const int N = 30;

double conversion(double input,int potnum){
    double result = pow(10.0,potnum);
    int temp = input * result;
    input = temp/result;
    return input;
}
Polynomial::Polynomial(){
    for(int i = 0; i < N; i++){
        x[i] = 0;
    }
}
Polynomial::Polynomial(char *str, bool &isarror) {
    for(int i = 0; i < N; i++){
        x[i] = 0;
    }
    double tmp = 0;
    int k = 0;
    int j = 1;
    bool ispow = false;
    bool isnag = false;
    bool isdec = false;
    for(int i = 0; str[i] != '\0'; i++){
        if(str[i] != '.' && str[i] != '+' && str[i] != '-' && str[i] != '^'
           && (str[i] - '0' >= 10 || str[i] - '0' < 0) && str[i] != 'x'){
            isarror = true;
            break;
        }
        //通过加减号来进行逐项输入
        if(str[i] == '+' || str[i] == '-'){
            isdec = false;
            if(isnag)x[k] += 0 - tmp;
            else x[k] += tmp;
            ispow = false;
            tmp = 0;
            k = 0;
            j = 1;
            if(str[i] == '-')isnag = true;
            else isnag = false;
        }
        if(str[i] == 'x' && str[i+1] == '^'){
            isdec = false;
            j = 1;
            ispow = true;
        }
        if(str[i] == 'x' && str[i+1] != '^' && str[i+1] != '+' && str[i+1] != '-' && str[i+1] != '\0')isarror = true;
        if(str[i] == 'x' && str[i+1] == '^' && str[i+2] == '-')isarror = true;
        if(str[i] - '0' < 10 && str[i] - '0' >= 0 && str[i+1] == '^')isarror = true;
        if(str[i] == '.')isdec = true;

        if(str[i] == 'x' && str[i+1] != '^')k = 1;
        if(ispow && str[i] - '0' < 10 && str[i] - '0' >= 0){
            k = 10*k + str[i] - '0';
        }

        if((str[i] == 'x' && i == 0) || (str[i] == 'x' &&
        (str[i-1] - '0' >= 10 || str[i-1] - '0' < 0)))tmp = 1;
        if(!ispow && str[i] - '0' < 10 && str[i] - '0' >= 0){
            if(isdec && str[i] == '.')isarror = true;
            if(isdec){
                tmp = tmp + (str[i]-'0')/pow(10,j);
                j++;
            }
            else tmp = 10*tmp + str[i] - '0';
        }
    }
    //补充最后一项
    if(isnag)x[k] += 0 - tmp;
    else x[k] += tmp;
    for(int i = 0; i < N; i++){
        if(x[i] != 0){
            x[i] = conversion(x[i],4);
        }
    }
}

void Polynomial::Out_Sta() {
    if(iszero())printf("%4.4f",0);
    else{
        int i1 = N-1;
        for(; i1 >= 0; i1--){
            if(x[i1] != 0 && i1 > 1){
                x[i1] = conversion(x[i1],4);
                printf("%4.4f",x[i1]);
                cout << 'x' << '^' << i1;
                break;
            }
            if(x[i1] != 0 && i1 == 1){
                x[i1] = conversion(x[i1],4);
                printf("%4.4f",x[i1]);
                cout << 'x';
                break;
            }
            if(x[i1] != 0 && i1 == 0){
                x[i1] = conversion(x[i1],4);
                printf("%4.4f",x[i1]);
                break;
            }
        }
        i1--;
        for(; i1 >= 0; i1--){
            if(x[i1] > 0)cout << '+';
            if(x[i1] != 0 && i1 > 1){
                x[i1] = conversion(x[i1],4);
                printf("%4.4f",x[i1]);
                cout << 'x' << '^' << i1;
            }
            if(x[i1] != 0 && i1 == 1){
                x[i1] = conversion(x[i1],4);
                printf("%4.4f",x[i1]);
                cout << 'x';
            }
            if(x[i1] != 0 && i1 == 0){
                x[i1] = conversion(x[i1],4);
                printf("%4.4f",x[i1]);
            }
        }
    }
}

bool Polynomial::iszero(){
    bool zero_det = true;
    for(int i = 0; i < N; i++){
        if(x[i] != 0){
            zero_det = false;
            break;
        }
    }
    return zero_det;
}

int Polynomial::maxpow(){
    int m = N-1;
    for(int i = N-1; i >= 0; i--){
        if(x[i] != 0){
            m = i;
            break;
        }
    }
    return m;
}

void divsion(Polynomial* A,Polynomial* B,Polynomial* res){
    int m, n;
    m = A->maxpow();
    n = B->maxpow();
    double tmp;
    for(int i = m-n; i >= 0; i--){
        res->x[i] = A->x[i+n]/B->x[n];
        for(int j = n; j >= 0; j--){
            A->x[i+j] =A->x[i+j] - B->x[j]*res->x[i];
        }
    }
}