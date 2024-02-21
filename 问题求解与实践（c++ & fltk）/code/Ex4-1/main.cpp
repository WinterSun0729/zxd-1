#include "std_lib_facilities.h"
#include <set>
#include "MyClass1.h"

string output;
ostringstream os(output);
set<string>var_sum;
vector<string>var_list;
vector<string> Right;
vector<string> Arror;
vector<double> b;
vector<double> solve_x;
int line = 0;
int row = 0;
bool isempty = true;

//非法输入归类
bool isright(string &str){
    int num_of_equal = 0;
    int here[26][100] = {0};//记录变元情况
    bool flag = true;
    bool isleft = true;
    int n = str.length();
    if(n <= 2)return false;
    for(int i = 0; i < n; i++){
        if(str[i] == '=')num_of_equal++;
    }
    if(num_of_equal != 1)return false;
    //单独讨论起始位置
    if(str[0] != '-' && !islower(str[0]) && !isdigit(str[0]))return false;
    else if(str[0] == '-'){
        if(!isdigit(str[1]) && !islower(str[1]))return false;
    }
    else if(islower(str[0])){
        if(!isdigit(str[1]))return false;
        for(int i1 = 0; i1 < 26; i1++){
            for(int j1 = 0; j1 < 100; j1++){
                if(here[i1][j1] == 1)return false;
            }
        }
        int j = 1;
        int k = 0;
        while (isdigit(str[j])){
            k = k * 10 + str[j] - '0';
            j++;
        }
        here[str[0] - 'a'][k] = 1;
    }
    else if(isdigit(str[0])){
        bool issinle;
        int j = 1;
        while(isdigit(str[j]) || str[j] == '.'){
            j++;
        }
        if(str[j] != '*')return false;
    }
    //第一位之后
    for(int i = 1; i < n; i++){
        if(str[i] != '.' && str[i] != '+' && str[i] != '-' && str[i] != '*' && str[i] != '=' && !islower(str[i]) && !isdigit(str[i]))return false;
        else if(str[i] == '.'){
            if(!isdigit(str[i+1]) || !isdigit(str[i-1]))return false;
        }
        else if(str[i] == '+'){
            if(!isleft)return false;
            if(!isdigit(str[i+1]) && !islower(str[i+1]))return false;
        }
        else if(str[i] == '-'){
            if(islower(str[i-1]))return false;
            if(!isdigit(str[i+1]) && !islower(str[i+1]))return false;
        }
        else if(str[i] == '*'){
            if(!isleft)return false;
            if(!isdigit(str[i-1]) || !islower(str[i+1]))return false;
        }
        else if(str[i] == '='){
            isleft = false;
            if((!isdigit(str[i+1]) && str[i+1] != '-') || !isdigit(str[i-1]) )return false;
        }
        else if(islower(str[i])){
            if(!isleft)return false;
            if(!isdigit(str[i+1]))return false;
            int k = 0;
            for (int j = i + 1; isdigit(str[j]); j++){
                k = k * 10 + str[j] - '0';
            }
            if(here[str[i] - 'a'][k] == 1)return false;
            else here[str[i] - 'a'][k] = 1;
        }
        else if(isdigit(str[i])){
            int j = i+1;
            while(isdigit(str[j]) || str[j] == '.'){
                j++;
            }
            if(str[j] != '*' && isleft && !islower(str[i-1]))return false;
        }
    }
    return flag;
}

//合法输入规范化
void Input_Sta(string &str, vector<double> &mat_coe, vector<string> &mat_var){
    line++;
    int n = str.length();
    int i = 0;
    //将等号左侧系数和变元存储
    while(str[i] != '=') {
        double coe = 1;
        string var;
        if(isdigit(str[i]) || str[i] == '-' || str[i] == '+') {
            int j = i + 1;
            while (isdigit(str[j]) || str[j] == '.') {
                j++;
            }
            if(str[i] == '-' && j == i+1)coe = -1;
            if(atof(str.substr(i,j-i).c_str()) == 0){}
            else coe = atof(str.substr(i,j-i).c_str());
            i = j;
            mat_coe.push_back(coe);
        }
        else if(islower(str[i])){
            if(i == 0)mat_coe.push_back(1);
            int j = i + 1;
            while (isdigit(str[j])) {
                j++;
            }
            var = str.substr(i,j-i);
            i = j;
            mat_var.push_back(var);
        }
        else i++;
    }
    if(str[i] == '='){
        b.push_back(atof(str.substr(i+1).c_str()));
    }
}
float conversion(float input,int potnum){
    float result = pow(10.0,potnum);
    int temp = input * result;
    input = temp/result;
    return input;
}

//请根据自己需求定义MyClass1和MyClass2
//定义main函数

int main()
{
    int cin_length = 0;
    /********** Begin **********/
    //读取测试输入
    vector<vector<pair<double,string>>> mat_be;
    while(cin){
        vector<double> mat_coe;
        vector<string> mat_var;
        vector<pair<double,string>> mat_be_i;

        string cin_str;
        getline(cin,cin_str);
        cin_length += cin_str.length() + 1;

        if(isright(cin_str)){
            isempty = false;
            Right.push_back(cin_str);
            Input_Sta(cin_str,mat_coe,mat_var);
            vector<double>::iterator coe_t = mat_coe.begin();
            vector<string>::iterator var_t = mat_var.begin();
            //将系数和元合成为pair对
            while (coe_t != mat_coe.end()) {
                mat_be_i.push_back({*coe_t,*var_t});
                coe_t++;
                var_t++;
            }
            mat_be.push_back(mat_be_i);//把每行的结果存起来
            continue;
        }
        else{
            Arror.push_back(cin_str);
            continue;
        }
    }
    //解析每个变量,存到set中,变量个数即为矩阵列数
    vector<vector<pair<double,string>>>::iterator mat_t = mat_be.begin();
    while (mat_t != mat_be.end()){
        for(vector<pair<double,string>>::iterator mat_ti = mat_t->begin(); mat_ti != mat_t->end(); mat_ti++){
            var_sum.insert(mat_ti->second);
        }
        mat_t++;
    }
    row = var_sum.size();
    for(auto t:var_sum){
        var_list.push_back(t);
    }
    if(isempty){
        cin_length -= 2;
        os << "Legal Equations:";
        for(auto& t:Right){
            os << endl << t ;
        }
        os <<endl << "Illegal Equations:";
        for(auto& t:Arror){
            os << endl << t;
        }
        string result = os.str();
        cout << cin_length << ':' << result.size()-1 << endl << result;
        return 0;
    }

    //转化为矩阵,开始矩阵运算
    Matrix_Opa Matrix(line, row, var_sum, mat_be, b);
    //Matrix.test_show();//监控矩阵情况
    int flag = Matrix.Cauculate(solve_x);
    //Matrix.test_show();//监控矩阵情况


    //请打印输出运算结果
    cin_length -= 2;
    os << "Legal Equations:";
    for(auto& t:Right){
        os << endl << t ;
    }
    if(flag != 0)os << endl << "error" << flag;
    else {
        for(int i = 0; i < row; i++){
            solve_x[i] = conversion(solve_x[i],4);
            os << endl << var_list[i] << ':' << fixed << setprecision(4) << solve_x[i];
        }
    }
    os <<endl << "Illegal Equations:";
    for(auto& t:Arror){
        os << endl << t;
    }
    string result = os.str();
    cout << cin_length << ':' << result.size()-1 << endl << result;

    /********** End **********/
    return 0;
}