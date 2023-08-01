#include "std_lib_facilities.h"
#include <map>

//deal函数将字符存到哈希表,并记录每个字符的重复次数
map<char, int> deal(string str){
    map<char, int> hmap;
    for(int i = 0; str[i] != '\0'; i++){
        char ch = str[i];
        auto t = hmap.find(ch);
        //找不到则加入元素
        if(t == hmap.end()){
            hmap.insert({ch,1});
        }
        //找到则将重复次数加一
        else{
            t->second += 1;
        }
    }
    return hmap;
}

//哈夫曼树结点
struct HNode{
    char data;//为记录多字母节点并比较字典序
    int weight;
    string Code;
    struct HNode *lchild;
    struct HNode *rchild;
};

//初始单根树构造
vector<HNode*> h;
void Creat_Ori_tree(map<char, int> haff_map){
    for(auto& t:haff_map){
        HNode* tmp = new HNode;
        tmp->data = t.first;
        tmp->weight = t.second;
        tmp->lchild = NULL;
        tmp->rchild = NULL;
        h.push_back(tmp);
    }
};

//按权值排序函数
void Sort(int n){
    for(int i = 1; i < n; i++){
        for(int j = 0; j < n-i; j++){
            if(h[j]->weight < h[j+1]->weight || (h[j]->weight == h[j+1]->weight && h[j]->data < h[j+1]->data)){
                HNode *t = h[j];
                h[j] = h[j+1];
                h[j+1] = t;
            }
        }
    }
}

//合并生成哈夫曼树
void Creat_Haff_tree(){
    int n = h.size();
    while(n > 1){
        Sort(n);
        HNode *s = new HNode;
        s->data = h[n-1]->data;
        s->lchild = h[n-1];
        s->rchild = h[n-2];
        s->weight = h[n-1]->weight + h[n-2]->weight;
        h[n-2] = s;
        n--;
    }
}

//生成哈夫曼代码
string code;
void PreOrder_Code(HNode *t){
    if(t){
        code.push_back('0');
        PreOrder_Code(t->lchild);
        code = code.substr(0,code.size()-1);

        code.push_back('1');
        PreOrder_Code(t->rchild);
        code = code.substr(0,code.size()-1);

        if (t->lchild == NULL && t->rchild == NULL){
            t->Code = code;
        }
    }
    return;
}

//将结果按照字典序保存
map<char, string> result_map;
void PreOrder(HNode *t){
    if (t){
        PreOrder(t->lchild);
        PreOrder(t->rchild);
        char ch;
        if (t->lchild == NULL && t->rchild == NULL){
            result_map.insert({t->data,t->Code});
        }
    }
}

//统计位长
int Count_Length(string str, map<char, string> result_map){
    int result = 0;
    for(int i = 0; i < str.length(); i++){
        result += result_map.find(str[i])->second.size();
    }
    return result;
}

ostringstream os;
int main(){
    /********** Begin **********/
    //读取测试输入
    string str;
    getline(cin,str);

    //输入字符统计
    int str_len = str.length();
    map<char, int> haff_map;
    haff_map = deal(str);

    Creat_Ori_tree(haff_map);
    Creat_Haff_tree();
    PreOrder_Code(h[0]);
    PreOrder(h[0]);
    int replace_len;
    replace_len = Count_Length(str,result_map);
    os << replace_len << endl;
    for(auto& t: result_map){
        os << t.first << ' ' << t.second << endl;
    }

    //打印输出运算结果
    cout << str_len << ':' << os.str().size()-1 << endl;
    cout << os.str().substr(0,os.str().size()-1);

    /********** End **********/
    return 0;
}