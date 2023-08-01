#include "S_window.h"

//------------------------------------------------------------------------------

S_window::S_window(Point xy, int w, int h, const string& title) :
    Window(xy,w,h,title),
    next_button(Point(x_max()-100,10), 70, 20, "确定", cb_next),
    in(Point(100,10),250,20,"File Position:"),
    date(Point(200,50),50,20,"date:"),
    button_pushed(false)
{
    attach(in);
    attach(date);
    attach(next_button);
}

//------------------------------------------------------------------------------

bool S_window::wait_for_button()

{
    show();
    button_pushed = false;
#if 1
    while (!button_pushed) Fl::wait();
    Fl::redraw();
#endif
    return button_pushed;
}

//------------------------------------------------------------------------------

void S_window::cb_next(Address, Address pw)
{  
    reference_to<S_window>(pw).next();    
}

//------------------------------------------------------------------------------

void S_window::next()
{
    button_pushed = true;
    text = in.get_string();
    want_date = date.get_string();
    hide();
}

//------------------------------------------------------------------------------
