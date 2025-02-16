#ifndef BIT_GUARD
#define BIT_GUARD

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

struct Binary_tree : Shape{
    Binary_tree(int n);
    vector<Point> get_ver(int n);
    virtual void draw_lines() const;
protected:
    const int r = 5;
    int sum;
    int level;
    Lines connect;
};

struct Binary_change : Binary_tree{
    Binary_change(int n);
    void draw_lines() const;
private:
    const int w = 10;
    const int h = 10;
};

struct BTree_window : Graph_lib::Window {
    BTree_window(Point xy, int w, int h, const string& title);
    Binary_tree* one;
    Binary_change* dou;
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