#include "std_lib_facilities.h"

struct Node;

class childTree {
private:
    Node* root;
public:
    childTree();
    childTree(string str);
    vector<Node*> generate(string str_left);
    string show_code();
    void clear(Node* t);
    ~childTree() {
        clear(root);
    }
};