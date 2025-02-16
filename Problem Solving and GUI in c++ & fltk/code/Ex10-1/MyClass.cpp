#include "MyClass.h"

struct Node {
    string code;
    vector<Node*> child;
    Node():child(NULL), code("10") {}
    // connect函数连接kid并生成标准签名
    void connect(vector<Node*> kid) {
        //sort保存孩子的代码用于排序
        list<string> sort;
        for(auto p:kid){
            child.push_back(p);
            sort.push_back(p->code);
        }
        sort.sort();
        code = code.substr(1,code.size()-2);
        for(auto p:sort){
            code += p;
        }
        code.push_back('0');
        code.insert(code.begin(),'1');
    }
};
childTree::childTree(){
    Node* t = new Node();
    Node* p = new Node();
    Node* k = new Node();
    Node* q = new Node();
    p->connect({t});
    k->connect({p});
    q->connect({k});
    root = q;
}
// 用递归函数解析输入表达式
// 每次递归先剥掉最外层"1,0"
// 之后找剩下字符串中首尾连续的{1,0}对
// 每找到一个便在返回结果vector中增加一个叶子节点
vector<Node*> childTree::generate(string str_left){
    vector<Node*> result;
    //剥去最外层
    str_left = str_left.substr(1,str_left.size()-2);
    //检查前端的叶子节点
    if(str_left.size() > 0){
        int i = 0;
        while (i < str_left.size() - 1 && str_left[i] != str_left[i + 1]){
            result.push_back(new Node());
            i += 2;
        }
        str_left = str_left.substr(i, str_left.size());
    }

    //检查尾端的叶子节点
    if(str_left.size() > 0){
        int i = str_left.size() - 1;
        while (i > 0 && str_left[i] != str_left[i - 1]){
            result.push_back(new Node());
            i -= 2;
        }
        str_left = str_left.substr(0, i + 1);
    }

    //剩下的节点归并实现
    if(!str_left.empty()){
        Node* tmp = new Node();
        tmp->connect(generate(str_left));
        result.push_back(tmp);
    }

    return result;
}

childTree::childTree(string str) {
    Node* t = new Node();
    t->connect(generate(str));
    root = t;
}
string childTree::show_code(){
    return root->code;
}
void childTree::clear(Node* t) {
    if (t == NULL) return;
    for(auto k:t->child){
        clear(k);
    }
    t->child.clear();
    delete(t);
    t = NULL;
}
