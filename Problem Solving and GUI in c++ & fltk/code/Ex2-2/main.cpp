#include<iostream>
#include "cmath"
#include "Polynomial.h"
using namespace std;
const int Ns = 300;

int main(){
    bool isarror = false;
    char str[Ns];
    cin.getline(str, Ns-1);
    Polynomial A(str,isarror);

    char str2[Ns];
    cin.getline(str2, Ns-1);
    Polynomial B(str2,isarror);

    //判断,当除式为零则报arror
    if(B.iszero())isarror = true;

    if(isarror){
        cout << "error";
        cout << endl;
        cout << "error";
        cout << endl;
        cout << "error";
        cout << endl;
        cout << "error";
        return 0;
    }
    A.Out_Sta();
    cout << endl;
    B.Out_Sta();
    cout << endl;
    Polynomial res;
    divsion(&A, &B, &res);
    res.Out_Sta();
    cout << endl;
    A.Out_Sta();

    return 0;
}