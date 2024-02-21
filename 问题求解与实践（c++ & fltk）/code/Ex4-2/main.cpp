#include "std_lib_facilities.h"
#include "Polynomial.h"

const int N = 30;
const int Ns = 300;
//请根据自己需求定义Polynomial
//定义main函数
int main()
{
    /********** Begin **********/
    //读取测试输入
    double x = 0,res = 0;
    char str[Ns] = {0};
    cin.getline(str,Ns-1);
    cin >> x;
    bool isarror = false;
    Polynomial A(str, isarror);
    if(isarror)cout << "error";
    else res = A.Solve(x);
    res = conversion(res,4);
    //请打印输出运算结果
    if(!isarror)printf("%4.4f",res);
    /********** End **********/
    return 0;
}
