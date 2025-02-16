#include "superellipse.h"
#include<cmath>
using namespace Graph_lib;

const int xmax = 600;
const int ymax = 400;
const int x_orig = xmax/2;
const int y_orig = ymax/2;
const Point orig(x_orig, y_orig); 
const int x_scale = 100;
const int y_scale = 100;

double a;
double b;
double m;
double n;
int N;

Sup_ellipes::Sup_ellipes(Point xy, int w, int h, const string& title)
:Window(xy,w,h,title),
next_button(Point(x_max()-150,0), 70, 20, "Show", cb_next),
quit_button(Point(x_max()-70,0), 50, 20, "Quit", cb_quit),
get_a(Point(20,0), 50, 20, "a:"),
get_b(Point(90,0), 50, 20, "b:"),
get_m(Point(160,0), 50, 20, "m:"),
get_n(Point(230,0), 50, 20, "n:"),
get_N(Point(300,0), 50, 20, "N:"){
attach(next_button);
attach(quit_button);attach(get_a);attach(get_b);attach(get_m);attach(get_n);attach(get_N);
attach(se);
}

void Sup_ellipes::cb_quit(Address, Address pw){reference_to<Sup_ellipes>(pw).quit();}
void Sup_ellipes::quit(){hide();}

void Sup_ellipes::cb_next(Address, Address pw){
    reference_to<Sup_ellipes>(pw).next();
}

void Sup_ellipes::next(){
    a = get_a.get_int();
    b = get_b.get_int();
    m = get_m.get_int();
    n = get_n.get_int();
    N = get_N.get_int()/4;

    //通过参数方程进行超椭圆上点的添加,均分方式为角度θ
    for(int i = 0; i < N; i++){
        double xi = x_orig + x_scale*a*pow(cos(i*3.14159/2/N),2.0/m);
        double yi = y_orig + y_scale*b*pow(sin(i*3.14159/2/N),2.0/n);
        points.push_back(Point(xi,yi));
    }
    for(int i = 0; i < N; i++){
        double xi = x_orig - x_scale*a*pow(cos((N-i)*3.14159/2/N),2.0/m);
        double yi = y_orig + y_scale*b*pow(sin((N-i)*3.14159/2/N),2.0/n);
        points.push_back(Point(xi,yi));
    }
    for(int i = 0; i < N; i++){
        double xi = x_orig - x_scale*a*pow(cos(i*3.14159/2/N),2.0/m);
        double yi = y_orig - y_scale*b*pow(sin(i*3.14159/2/N),2.0/n);
        points.push_back(Point(xi,yi));
    }
    for(int i = 0; i <= N; i++){
        double xi = x_orig + x_scale*a*pow(cos((N-i)*3.14159/2/N),2.0/m);
        double yi = y_orig - y_scale*b*pow(sin((N-i)*3.14159/2/N),2.0/n);
        points.push_back(Point(xi,yi));
    }
    //以下for循环获得测试show2
    for(int i = 0; i < number_of_points(); i++){
        for(int j = 0; j < number_of_points(); j++){
            if(j != i){
                se.add(points[i]);
                se.add(points[j]);
                se.add(points[i]);
            }
        }
    }
    //以下for循环获得测试show1
    // for(int i = 0; i < number_of_points(); i++){
    //     se.add(points[i]);
    // }

    redraw();
}