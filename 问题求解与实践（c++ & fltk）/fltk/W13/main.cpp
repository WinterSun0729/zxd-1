#include "Simple_window.h"
#include "star.h"
#include "binary_tree.h"

//------------------------------------------------------------------------------

int main()
{
    using namespace Graph_lib;
    //1.Star
    // Star_window win(Point(100,100),600,400,"Star");
    // return gui_main();

    //2,3.Binary_tree
    BTree_window win(Point(100,100),600,400,"Binary Tree");
    return gui_main();
}

//------------------------------------------------------------------------------
