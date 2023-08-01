#include "star.h"
using namespace Graph_lib;

const int xmax = 600;
const int ymax = 400;
const int x_orig = xmax/2;
const int y_orig = ymax/2;
const Point orig(x_orig, y_orig);
const int x_scale = 100;
const int y_scale = 100;
int N;

Star_window::Star_window(Point xy, int w, int h, const string& title)
:Window(xy,w,h,title),
next_button(Point(x_max()-150,0), 70, 20, "Show Star", cb_next),
quit_button(Point(x_max()-70,0), 70, 20, "Quit", cb_quit),
next_num(Point(x_max()-510,0), 50, 20, "add number:"){
    attach(next_button);
    attach(quit_button); attach(next_num);
    attach(one);attach(dou);
}
void Star_window::cb_quit(Address, Address pw){reference_to<Star_window>(pw).quit();}
void Star_window::quit(){hide();}
void Star_window::cb_next(Address, Address pw){reference_to<Star_window>(pw).next();}
void Star_window::next(){
    N = next_num.get_int();
    for(int i = 0; i < N; i++){
        double xi = x_orig + x_scale*cos(i*3.14159*2/N);
        double yi = y_orig + y_scale*sin(i*3.14159*2/N);
        ps.push_back(Point(xi,yi));
    }
        int i = 0;
        int j = (i + 2) % ps.size();
        while (j != i)
        {
            one.add(ps[j]);
            j = (j + 2) % ps.size();
        }
        one.add(ps[0]);
        one.add(ps[(i + 2) % ps.size()]);
    if(ps.size() % 2 == 0){
        int i = 1;
        int j = (i + 2) % ps.size();
        while (j != i)
        {
            dou.add(ps[j]);
            j = (j + 2) % ps.size();
        }
        dou.add(ps[1]);
        dou.add(ps[(i + 2) % ps.size()]);
    }
    //在此填色
    //one.set_color(Color::dark_green);
    one.set_fill_color(Color::yellow);
    //dou.set_color(Color::dark_green);
    dou.set_fill_color(Color::yellow);
    redraw();
}