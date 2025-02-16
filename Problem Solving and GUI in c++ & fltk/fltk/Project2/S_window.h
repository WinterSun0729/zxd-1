#ifndef S_WINDOW_GUARD
#define S_WINDOW_GUARD 1

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

//------------------------------------------------------------------------------

struct S_window : Graph_lib::Window {
    S_window(Point xy, int w, int h, const string& title );
    string text;
    string want_date;
    In_box in;
    In_box date;
    bool wait_for_button();
    bool button_pushed;
private:
    Button next_button;
    static void cb_next(Address, Address);
    void next();
};

#endif
