#include "MyClass.h"

bool valid_flag = true;
//进行括号匹配,若有未配对则invalid
bool isvalid(string &str){
    stack<char> T;
    for(int i = 0; i < str.size(); i++){
        if(str[i] == '1'){
            if(T.empty() && i != 0)return false;
            T.push('1');
        }
        else{
            if(T.empty())return false;
            else T.pop();
        }
    }
    return T.empty();
}

ostringstream os;

int main() {
    int input_len = 0;
    string tree1;
    string tree2;
    getline(cin,tree1);
    getline(cin,tree2);
    input_len = tree1.size() + tree2.size() + 1;
    if(!isvalid(tree1) && !isvalid(tree2)){
        os << "Invalid tree(s): " << tree1 << " " << tree2;
    }
    else if(!isvalid(tree1))os << "Invalid tree(s): " << tree1;
    else if(!isvalid(tree2))os << "Invalid tree(s): " << tree2;
    else {
        childTree t1(tree1);
        childTree t2(tree2);
        //cout << t1.show_code() << endl << t2.show_code();
        if(t1.show_code() == t2.show_code())os << tree1 << " and " << tree2 << " are isomorphic";
        else os << tree1 << " and " << tree2 << " are non-isomorphic";
    }
    cout << input_len << ':' << os.str().size() << endl << os.str();
}
