#include "std_lib_facilities.h"
#include <algorithm>
#include <set>
#include <iostream>
#include <string>
#include <iterator>
#include <vector>

class Bcompare{
private:
    string data;
public:
    Bcompare(string str):data(str){}
    string getstr()const{return data;}
};
bool operator< (const Bcompare &st1, const Bcompare &st2){
    string t1 = st1.getstr();
    string t2 = st2.getstr();
    for(int i = 0; i < t1.size(); i++){
        if(!islower(t1[i])) t1[i] += 32;
    }
    for(int i = 0; i < t2.size(); i++){
        if(!islower(t2[i])) t2[i] += 32;
    }
    if(t1 != t2){
        return t1 > t2;
    }
    else{
        if(st1.getstr() == st2.getstr())return 0;
        else return 1;
    }
}
bool operator== (const Bcompare &st1, const Bcompare &st2){
    return st1.getstr() == st2.getstr();
}
ostream& operator<< (ostream& os, const Bcompare &st){
    os << st.getstr();
    return os;
}

int main()
{
    string str;
    set<string> solveA;
    set<Bcompare> solveB;
    while(cin){
        getline(cin,str);
        solveA.insert(str);
        solveB.insert(Bcompare(str));
    }

    cout << "rule a:" << endl;
    for(auto t: solveA){
        cout << t << endl;
    }
    cout << "rule b:";
    for(auto t: solveB){
        cout << endl << t;
    }

    return 0;
}