#ifndef STAR_GUARD
#define STAR_GUARD

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

struct Star_window : Graph_lib::Window {
    Star_window(Point xy, int w, int h, const string& title);
    Open_polyline one;
    Open_polyline dou;
    vector<Point> ps;
private:
    Button next_button;
    Button quit_button;
    In_box next_num;
    void next();
    void quit();
    static void cb_next(Address, Address window);
    static void cb_quit(Address, Address window);
};

#endif