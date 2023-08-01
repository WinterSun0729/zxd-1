#include "binary_tree.h"
using namespace Graph_lib;

const int xmax = 600;
const int ymax = 400;
const int x_orig = xmax/2;
const int y_begin = 20;
const int y_orig = ymax/2;
const Point orig(x_orig, y_orig);
const double dis = 300;//第二层节点间距为 dis*x_scale
const int wid = 20;//两层间距为 wid*y_scale
int n_of_tree = 1;

vector<Point> Binary_tree::get_ver(int n){
    if(n == 0) return{};
    if(n == 1) return{Point(x_orig, y_begin)};
    vector<Point> result;
    for(auto t:get_ver(n-1)){
        result.push_back(Point(t.x-(dis/pow(2.0,n)),t.y+wid*n));
        result.push_back(Point(t.x+(dis/pow(2.0,n)),t.y+wid*n));
    }
    return result;
}

Binary_tree::Binary_tree(int n){
    level = n;
    for(int k = 2; k <= n; k++){
        for(int i = 0; i < pow(2,k-1); i++){
        int j = i/2;
        connect.add(get_ver(k-1)[j],get_ver(k)[i]);
        }
    }
    for(int i = 1; i <= n; i++){
        for(auto t:get_ver(i)){
        add(Point(t.x-r,t.y-r));
        sum++;
        }
    }
}
void Binary_tree::draw_lines() const
{
    connect.draw_lines();
    if (color().visibility()){
        for(int i = 0; i < sum; i++){
            fl_arc(point(i).x,point(i).y,r+r,r+r,0,360);
        }
    }
}

Binary_change::Binary_change(int n):Binary_tree(n){}
void Binary_change::draw_lines() const
{
    connect.draw_lines();
    if (color().visibility()){
        for(int i = 0; i < sum; i++){
            fl_rect(point(i).x,point(i).y,w,h);
        }
    }
}

BTree_window::BTree_window(Point xy, int w, int h, const string& title)
:Window(xy,w,h,title),
next_button(Point(x_max()-150,0), 70, 20, "Show Tree", cb_next),
quit_button(Point(x_max()-70,0), 70, 20, "Quit", cb_quit),
next_num(Point(x_max()-510,0), 50, 20, "add number:"){
    attach(next_button);
    attach(quit_button); attach(next_num);
}
void BTree_window::cb_quit(Address, Address pw){reference_to<BTree_window>(pw).quit();}
void BTree_window::quit(){hide();}
void BTree_window::cb_next(Address, Address pw){reference_to<BTree_window>(pw).next();}
void BTree_window::next(){
    detach(*dou);
    n_of_tree = next_num.get_int();
    dou = new Binary_change(n_of_tree);
    attach(*dou);
    redraw();
}