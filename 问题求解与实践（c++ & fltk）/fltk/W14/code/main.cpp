#include "analog_clock.h"
#include <sstream>
#include <iomanip>
#include <chrono>

using namespace Graph_lib;
using namespace std;

int main(){
	S_window *win = new S_window(Point(100,100),600,800,"clock");
	
	//绘制时钟边框
	Circle *frame = new Circle(Point(300,300),200);
	Line_style bold(Line_style::solid, 5);
	frame->set_style(bold);
	win->attach(*frame);
	
	//绘制时钟刻度
	vector<Point> mark;
	for(int i = 0; i < 12; i++){
		int x0 = 300 + 170*cos(2*3.14*i/12);
		int y0 = 300 + 170*sin(2*3.14*i/12);
		int x1 = 300 + 190*cos(2*3.14*i/12);
		int y1 = 300 + 190*sin(2*3.14*i/12);
		int x2 = 300 + 200*cos(2*3.14*i/12);
		int y2 = 300 + 200*sin(2*3.14*i/12);
		mark.push_back(Point(x0,y0));
		Line *one = new Line(Point(x1,y1),Point(x2,y2));
		one->set_style(bold);
		win->attach(*one);
	}

	//绘制时钟对应数字
	vector<string> num;
	num.push_back("3");num.push_back("4");num.push_back("5");num.push_back("6");
	num.push_back("7");num.push_back("8");num.push_back("9");num.push_back("10");
	num.push_back("11");num.push_back("12");num.push_back("1");num.push_back("2");
	for(int i = 0; i < 12; i++){
		Text *s_num = new Text(mark[i],num[i]);
		s_num->set_font(Font::courier_bold);
		win->attach(*s_num);
	}

	//获取系统日期时间转换为整数
	SYSTEMTIME sys;
    GetLocalTime(&sys);
    stringstream ss;
    auto t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    ss << std::put_time(std::localtime(&t), "%Y-%m-%d-%H-%M-%S");
	int count_ = 0;
	int i = 0;
	string Ytr, Mtr, Dtr, htr, mtr, str;
if(true){
	while (ss.str()[i] != '-'){
		Ytr.push_back(ss.str()[i]);
		i++;
	}
	i++;
	while (ss.str()[i] != '-'){
		Mtr.push_back(ss.str()[i]);
		i++;
	}
	i++;
	while (ss.str()[i] != '-'){
		Dtr.push_back(ss.str()[i]);
		i++;
	}
	i++;
	while (ss.str()[i] != '-'){
		htr.push_back(ss.str()[i]);
		i++;
	}
	i++;
	while (ss.str()[i] != '-'){
		mtr.push_back(ss.str()[i]);
		i++;
	}
	i++;
	while (ss.str()[i] != '\0'){
		str.push_back(ss.str()[i]);
		i++;
	}
}
	int hour = atoi(htr.c_str());int min = atoi(mtr.c_str());int sec = atoi(str.c_str());

	//显示时间
	Clock now;
	Text_Clock t_now;
	int all_time = 3600 * hour + 60 * min + sec - 1;
	while (!win->button_pushed){
		win->redraw();
		now.dedraw(win);
		t_now.TC_dedraw(win);
		all_time++;
		hour = all_time / 3600; min = (all_time - 3600 * hour) / 60; sec = (all_time - 3600 * hour - 60 * min);
		now.draw(win,hour,min,sec);
		stringstream *sss;
		sss = new stringstream;
		*sss <<Ytr<<"/"<<Mtr<<"/"<<Dtr<<"  "<<hour<<" : "<<min<<" : "<<sec;
		t_now.TC_draw(win,sss->str());
		delete sss;
		Fl::wait();
		Sleep(1000);
	}
	return Fl::run();
}