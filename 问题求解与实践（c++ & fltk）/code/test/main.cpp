#include "std_lib_facilities.h"

struct Distribution{
    string date;
    int M;
    int D;
    int h_tem;
    int l_tem;
public:
    Distribution(){};
    Distribution(string d, int h, int l):date(d),h_tem(h),l_tem(l){
        stringstream st;
        st << date;
        int month,day;
        char p;
        st >> month >> p >> day;
        M = month;
        D = day;
    }
};
//拉格朗日插值法预测数值
double lagrange(vector<double> x, vector<double> y, double xx, int n) {
    int i, j;
    vector<double> a;
    double yy = 0.0;
    for (i = 0; i < n; ++i) {
        a.push_back(y[i]);
    }
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            if (j != i)a[i] *= (xx - x[j]) / (x[i] - x[j]);
        }
        yy += a[i];
    }
    return yy;
}
vector<double> data_x;
vector<double> data_yhigh;
vector<double> data_ylow;
int main(){
    string file_name = "C:\\MinGW\\msys\\1.0\\home\\"
                       "Dong\\program\\p2\\data.txt";
    string give_date = "09-01";
    ifstream ifs;
    stringstream ss;
    ifs.open(file_name);
    if (!ifs) {                                 //错误处理
        cout << "file missed";
        return 1;
    }
    string file_in;
    vector<string> file_store;
    while (ifs >> file_in){
        file_store.push_back(file_in);
    }

    //数据存储
    map<string, Distribution> w_data;
    string d_tmp;
    int h_tmp;
    int l_tmp;
    for(int i = 0; i < file_store.size(); i++){//分三组进行输入
        if(i % 3 == 0){
            d_tmp = file_store[i];
            data_x.push_back(i/3);
        }
        else if(i % 3 == 1){
            stringstream s_tmp;
            s_tmp << file_store[i];
            s_tmp >> h_tmp;
        }
        else{
            stringstream s_tmp;
            s_tmp << file_store[i];
            s_tmp >> l_tmp;
            w_data.insert({d_tmp, Distribution(d_tmp, h_tmp, l_tmp)});
            data_yhigh.push_back(h_tmp);
            data_ylow.push_back(l_tmp);
        }
    }

    vector<string> d_bef;
    d_bef.push_back("11-01");d_bef.push_back("11-02");d_bef.push_back("11-03");
    d_bef.push_back("11-04");d_bef.push_back("11-05");d_bef.push_back("11-06");
    int mark_tail = data_x[60] + 1;
    for(int i = 0; i < 6; i++){                 //以全体数据为源,给出 n=2 的拉格朗日估计
        w_data.insert({d_bef[i],Distribution(d_bef[i],
        int(lagrange(data_x,data_yhigh,mark_tail+i,1)),
        int(lagrange(data_x,data_ylow,mark_tail+i,1)))});
    }
    for(auto t:w_data){
        cout << t.second.date << ':'
        << t.second.h_tem << ' ' << t.second.l_tem << endl;
    }
//    vector<double> data_xb, data_yhighb, data_ylowb;
//    for(int i = 0; i < 30; i++){
//        data_xb.push_back(data_x[i]);
//        data_yhighb.push_back(data_yhigh[i]);
//        data_ylowb.push_back(data_ylow[i]);
//    }
//    cout << lagrange(data_xb,data_yhighb,3,3);
    ifs.close();
}