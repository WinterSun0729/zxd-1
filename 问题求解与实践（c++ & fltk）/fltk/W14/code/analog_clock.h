#ifndef CLK_GUARD
#define CLK_GUARD

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
#include <cmath>
#include "std_lib_facilities.h"
#include <time.h>
using namespace Graph_lib;

//S-window模仿Simple_window,将bool button_pushed变为公有,防止退出后进入后台
struct S_window : Graph_lib::Window {
    S_window(Point xy, int w, int h, const string& title );
    bool button_pushed;

private:
    Graph_lib::Button next_button;
    static void cb_next(Graph_lib::Address, Graph_lib::Address);
    void next();

};

//------------------------------------------------------------------------------

class Clock{
private:
    Line *h_pter, *m_pter, *s_pter;
public:
	Clock() {}
	~Clock();
    void draw(S_window *win, int hour, int min, int sec);
    void dedraw(S_window *win);
};

//------------------------------------------------------------------------------

class Text_Clock{
private:
    Text *tx;
public:
	Text_Clock() {}
	~Text_Clock();
    void TC_draw(S_window *win, string Data);
    void TC_dedraw(S_window *win);
};

#endif