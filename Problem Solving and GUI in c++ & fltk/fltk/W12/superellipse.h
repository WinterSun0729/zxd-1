#ifndef SPE_GUARD
#define SPE_GUARD

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include "Simple_window.h"
#include <FL/Fl_Button.H>
#include <FL/Fl_Output.H>
#include "GUI.h"
#include "Graph.h"
using namespace Graph_lib;


struct Sup_ellipes : Graph_lib::Window{
    Sup_ellipes(Point xy, int w, int h, const string& title);
    vector<Point> points;
    int number_of_points() const { return int(points.size()); }
    Open_polyline se;
private:
    Button quit_button;
    Button next_button;
    In_box get_a;
    In_box get_b;
    In_box get_m;
    In_box get_n;
    In_box get_N;
    void next();
    void quit();
    static void cb_next(Address, Address window);
    static void cb_quit(Address, Address window);
};


#endif