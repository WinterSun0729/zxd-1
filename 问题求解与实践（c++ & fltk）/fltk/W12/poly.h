#ifndef POLY_GUARD
#define POLY_GUARD

#include <FL/Fl.H>
#include <FL/Fl_GIF_Image.H>
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include "Simple_window.h"
#include <FL/Fl_Button.H>
#include <FL/Fl_Output.H>
#include "GUI.h"
#include "Graph.h"
using namespace Graph_lib;

struct Poly : Closed_polyline {    // closed sequence of non-intersecting lines
    void add(Point p);
    void draw_lines() const;
};

struct Poly_Win : Graph_lib::Window{
    Poly_Win(Point xy, int w, int h, const string& title);
    Simple_window win(Point xy, int w, int h, const string& title);
    vector<Point> points;
    Poly poly;
private:
    Button quit_button;
    Button next_button;
    Button show_button;
    In_box next_x;
    In_box next_y;
    Out_box is_poly;
    void next();
    void show();
    void quit();
    static void cb_next(Address, Address window);
    static void cb_show(Address, Address window);
    static void cb_quit(Address, Address window);
};

#endif