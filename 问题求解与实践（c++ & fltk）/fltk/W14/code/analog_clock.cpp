#include "analog_clock.h"
using namespace Graph_lib;

S_window::S_window(Point xy, int w, int h, const string& title) :
    Window(xy,w,h,title),
    next_button(Point(x_max()-70,0), 70, 20, "Quit", cb_next),
    button_pushed(false)
{
    attach(next_button);
}
void S_window::cb_next(Graph_lib::Address, Graph_lib::Address pw)
{
    Graph_lib::reference_to<S_window>(pw).next();
}
void S_window::next()
{
    button_pushed = true;
    hide();
}

//------------------------------------------------------------------------------

void Clock::dedraw(S_window *win){
    win->detach(*h_pter);
	win->detach(*m_pter);
	win->detach(*s_pter);
}

Clock::~Clock(){
	delete h_pter;
    delete m_pter;
    delete s_pter;
}

void Clock::draw(S_window *win, int hour, int min, int sec){
    //画出时针,分针,秒针
    double han = 2*3.14*(hour%12)/12;
    double man = 2*3.14*min/60;
    double san = 2*3.14*sec/60;
    h_pter = new Line(Point(300,300),Point(300 + 100*sin(han),300 - 100*cos(han)));
    m_pter = new Line(Point(300,300),Point(300 + 130*sin(man),300 - 130*cos(man)));
    s_pter = new Line(Point(300,300),Point(300 + 150*sin(san),300 - 150*cos(san)));
    //设置粗细
    Line_style hbold(Line_style::solid,8);
    Line_style mbold(Line_style::solid,4);
    Line_style sbold(Line_style::solid,2);
    h_pter->set_style(hbold);
    m_pter->set_style(mbold);
    s_pter->set_style(sbold);

    win->attach(*h_pter);
    win->attach(*m_pter);
    win->attach(*s_pter);
}

//------------------------------------------------------------------------------

Text_Clock::~Text_Clock(){
    delete tx;
}
void Text_Clock::TC_dedraw(S_window *win){
    win->detach(*tx);
}
void Text_Clock::TC_draw(S_window *win, string Data){
    tx = new Text(Point(145,600),Data);
    tx->set_font_size(32);
    tx->set_font(Font::helvetica_bold);
    win->attach(*tx);
}
