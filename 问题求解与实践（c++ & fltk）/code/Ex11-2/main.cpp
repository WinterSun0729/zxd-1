#include "std_lib_facilities.h"
#include <set>

class Position{
private:
    pair<int, int> site;
public:
    Position(int x, int y){
        site.first = x;
        site.second = y;
    }
    pair<int, int> getpos()const{return site;}
    bool out_dis(int x0, int y0, double d){
        int dx = site.first - x0;
        int dy = site.second - y0;
        return sqrt(dx*dx + dy*dy) > d;
    }
};
bool operator<(const Position &st1, const Position &st2){
    return st1.getpos().first < st2.getpos().first || st1.getpos().second < st2.getpos().second;
}
bool operator== (const Position &st1, const Position &st2){
    return st1.getpos() == st2.getpos();
}
ostream& operator<< (ostream& os, const Position &st){
    os << '(' << st.getpos().first << ", " << st.getpos().second << ')';
    return os;
}

int sort_x, sort_y;
bool cmp(const Position &st1, const Position &st2){
    int dx1 = st1.getpos().first - sort_x;
    int dy1 = st1.getpos().second - sort_y;
    int dx2 = st2.getpos().first - sort_x;
    int dy2 = st2.getpos().second - sort_y;
    return (dx1*dx1 + dy1*dy1) < (dx2*dx2 + dy2*dy2);
}

bool isnum(char ch){
    return isdigit(ch) || ch == '-';
}

bool isvalid(string str_in){
    bool flag = false;
    bool flag1 = false;
    bool flag2 = false;
    bool flag3 = false;
    for(int k = 0; k < str_in.size(); k++){
        string dir;
        while (islower(str_in[k])){
            dir.push_back(str_in[k]);
            k++;
        }
        if(dir == "add"){
            k++;
            string str;
            str = str_in.substr(k);
            stringstream ss;
            ss << str;
            int n;
            ss >> n;
            while (isnum(str_in[k])){
                k++;
            }
            for(int i = 0; i < 2 * n; i++){
                k++;
                if (!isnum(str_in[k])) return false;
                while (isnum(str_in[k]) || str_in[k] == '-'){
                    k++;
                }
            }
            if(str_in[k] != '\0') return false;
            flag = true;
        }
        else if(dir == "find"){
            k++;
            while (isnum(str_in[k])){
                k++;
                flag1 = true;
            }
            k++;
            while (isnum(str_in[k])){
                k++;
                flag2 = true;
            }
            flag = flag1 && flag2;
        }
        else if(dir == "filter"){
            k++;
            while (isnum(str_in[k])){
                k++;
                flag1 = true;
            }
            k++;
            while (isnum(str_in[k])){
                k++;
                flag2 = true;
            }
            k++;
            while (isnum(str_in[k])){
                k++;
                flag3 = true;
            }
            flag = flag1 && flag2 && flag3;
        }
        else if(dir == "sort"){
            k++;
            while (isnum(str_in[k])){
                k++;
                flag1 = true;
            }
            k++;
            while (isnum(str_in[k])){
                k++;
                flag2 = true;
            }
            flag = flag1 && flag2;
        }
        else return flag;
    }
    return flag;
}

int main()
{
    set<Position> tmp;
    vector<Position> solve;
    while (cin){
        string str_in;
        getline(cin, str_in);
        if (str_in == "")break;
        if (!isvalid(str_in)){
            cout << "invalid input" << endl;
            continue;
        }
        stringstream ss;
        ss << str_in;
        string dir = "";
        ss >> dir;
        if(dir == "add"){
            solve.clear();
            int n;
            ss >> n;
            for (int i = 0; i < n; ++i) {
                int x, y;
                ss >> x >> y;
                tmp.insert({x,y});
            }
            for(auto t: tmp){
                solve.push_back(t);
            }
            cout << solve.size() << endl;
        }
        else if(dir == "find"){
            int x, y;
            ss >> x >> y;
            Position fi(x,y);
            if(find(solve.begin(),solve.end(),fi) != solve.end())cout << "find" << endl;
            else cout << "not find" << endl;
        }
        else if(dir == "filter"){
            int x0, y0;
            double d;
            ss >> x0 >> y0 >> d;
            vector<Position>::iterator it = solve.begin();
            while(it != solve.end()){
                if (it->out_dis(x0, y0, d)){
                    if(it == solve.end()-1){
                        solve.erase(it);
                        break;
                    }
                    solve.erase(it);
                }
                else{
                    if(it == solve.end()-1)break;
                    it++;
                }
            }
            cout << solve.size() << endl;
        }
        else if(dir == "sort"){
            ss >> sort_x >> sort_y;
            sort(solve.begin(),solve.end(),cmp);
            for(int i = 0; i < solve.size(); i++){
                if (i == solve.size() - 1)cout << solve[i];
                else cout << solve[i] << ", ";
            }
            cout << endl;
        }
        else break;
    }

    return 0;
}