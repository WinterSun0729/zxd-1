#include <FL/Fl.H>
#include <FL/Fl_GIF_Image.H>
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include "S_window.h"
#include <FL/Fl_Button.H>
#include <FL/Fl_Output.H>
#include "GUI.h"
#include "Graph.h"
#include <map>
using namespace Graph_lib;

struct Distribution{
    string date;
    int M;
    int D;
    int h_tem;
    int l_tem;
public:
    Distribution(){};
    Distribution(string d, int h, int l):date(d),h_tem(h),l_tem(l){
        stringstream st;
        st << date;
        int month,day;
        char p;
        st >> month >> p >> day;
        M = month;
        D = day;
    }
};

//Weather Window 的数值
const int xmax = 800;
const int ymax = 600;
const int xoffset = 80;
const int yoffset = 60;
const int xspace = 40;
const int yspace = 40;
const int xlength = xmax-xoffset-xspace;
const int ylength = ymax-yoffset-yspace;
const double xscale = double(xlength)/7;
const double yscale = double(ylength)/40;

//给定年月日, 输出当天是星期几
//函数实现为Zeller公式
int ReturnWeekDay( unsigned int iYear, unsigned int iMonth, unsigned int iDay )
{
    int iWeek = 0;
    unsigned int y = 0, c = 0, m = 0, d = 0;
    if ( iMonth == 1 || iMonth == 2 ){
        c = ( iYear - 1 ) / 100;
        y = ( iYear - 1 ) % 100;
        m = iMonth + 12;
        d = iDay;
    }
    else{
        c = iYear / 100;
        y = iYear % 100;
        m = iMonth;
        d = iDay;
    }
    iWeek = y + y / 4 + c / 4 - 2 * c + 26 * ( m + 1 ) / 10 + d - 1;    //蔡勒公式
    iWeek = iWeek >= 0 ? ( iWeek % 7 ) : ( iWeek % 7 + 7 );             //iWeek为负时取模
    if ( iWeek == 0 ){ 
        iWeek = 7;
    }
    return iWeek;
}

//拉格朗日插值法预测数值
double lagrange(vector<double> x, vector<double> y, double xx, int n) {
    int i, j;
    vector<double> a;
    double yy = 0.0;
    for (i = 0; i < n; ++i) {
        a.push_back(y[i]);
    }
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            if (j != i)a[i] *= (xx - x[j]) / (x[i] - x[j]);
        }
        yy += a[i];
    }
    return yy;
}
vector<double> data_x;
vector<double> data_yhigh;
vector<double> data_ylow;

int main()
{
    using namespace Graph_lib;   // our graphics facilities are in Graph_lib
    S_window win(Point(100,100),500,100,"Weather-getfile");
    if(win.wait_for_button()){
        Simple_window win2(Point(100,200),800,600,"Weather");
        
        //文件数据获取
        string file_name = win.text;
        string give_date = win.want_date;
        ifstream ifs;
        stringstream ss;
        ifs.open(file_name);
        if (!ifs) {                                 //错误处理
            ss << "file missed";
            Text test(Point(100,100),ss.str());
            win2.attach(test);
            win2.wait_for_button();
            return 1;
        }
        string file_in;
        vector<string> file_store;
        while (ifs >> file_in){
            file_store.push_back(file_in);
        }
        
        //数据存储
        map<string, Distribution> w_data;
        string d_tmp;
        int h_tmp;
        int l_tmp;
        for(int i = 0; i < file_store.size(); i++){//分三组进行输入
            if(i % 3 == 0){
                d_tmp = file_store[i];
                data_x.push_back(i/3);
            }
            else if(i % 3 == 1){
                stringstream s_tmp;
                s_tmp << file_store[i];
                s_tmp >> h_tmp;
            }
            else{
                stringstream s_tmp;
                s_tmp << file_store[i];
                s_tmp >> l_tmp;
                w_data.insert({d_tmp, Distribution(d_tmp, h_tmp, l_tmp)});
                data_yhigh.push_back(h_tmp);
                data_ylow.push_back(l_tmp);
            }
        }
        ifs.close();

        //图表绘制-坐标轴
        Axis x(Axis::x, Point(xoffset,ymax-yoffset), xlength, 7);
        Axis y(Axis::y, Point(xoffset,ymax-yoffset), ylength, 8);
        Text y_num1(Point(xoffset-20,ymax-yoffset),"0");
        Text y_num2(Point(xoffset-50,ymax-yoffset-ylength + 7),"温度 40");
        Text y_num3(Point(xoffset-20,ymax-yoffset-ylength/4 + 6),"10");
        Text y_num4(Point(xoffset-20,ymax-yoffset-ylength/2 + 5),"20");
        Text y_num5(Point(xoffset-20,ymax-yoffset-3*ylength/4 + 4),"30");
        Text x_tex(Point(xmax-xspace-20,ymax-yoffset+20),"日期");
        win2.attach(x);
        win2.attach(y);
        win2.attach(y_num1);
        win2.attach(y_num2);
        win2.attach(y_num3);
        win2.attach(y_num4);
        win2.attach(y_num5);
        win2.attach(x_tex);

        //图像绘制-已存在数据折线
        map<string, Distribution>::iterator g_day;
        g_day = w_data.find(give_date);
        if(g_day == w_data.end()){                  //错误处理
            ss << "wrong date";
            Text test(Point(100,100),ss.str());
            win2.attach(test);
            win2.wait_for_button();
            return 2;
        }
        bool is_head = false;
        bool is_tail = false;
        int weekday = ReturnWeekDay(2022,g_day->second.M,g_day->second.D);
        for(weekday ; weekday > 1; weekday--){       //给出指定日期的周一指针
            if(g_day == w_data.begin()){
                is_head = true;
                break;                               //判断到头部,需要预测
            }
            g_day--;
        }
        map<string, Distribution>::iterator g_day2 = g_day;
        for(int i = weekday; i <= 7; i++){
            if(g_day2 == w_data.end()){
                is_tail = true;
                break;                               //判断到尾部,需要预测
            }
            g_day2++;
        }
        if(!is_head && !is_tail){
        Open_polyline high_t, low_t;
        vector<string> dt;
        for(int i = 1; i <= 7; i++){
            high_t.add(Point(xoffset + (i-1)*xscale, 
                ymax-yoffset-(g_day->second.h_tem)*yscale+5));
            low_t.add(Point(xoffset + (i-1)*xscale, 
                ymax-yoffset-(g_day->second.l_tem)*yscale+5));
                dt.push_back(g_day->second.date);
                g_day++;
        }
        high_t.set_style(Line_style::solid);
        high_t.set_color(Color::dark_red);
        low_t.set_style(Line_style::solid);
        low_t.set_color(Color::dark_blue);
        win2.attach(high_t);
        win2.attach(low_t);

        //日期标签绘制
        Text dt1(Point(xoffset, ymax-yoffset+20),dt[0]);
        Text dt2(Point(xoffset + xscale, ymax-yoffset+20),dt[1]);
        Text dt3(Point(xoffset + 2*xscale, ymax-yoffset+20),dt[2]);
        Text dt4(Point(xoffset + 3*xscale, ymax-yoffset+20),dt[3]);
        Text dt5(Point(xoffset + 4*xscale, ymax-yoffset+20),dt[4]);
        Text dt6(Point(xoffset + 5*xscale, ymax-yoffset+20),dt[5]);
        Text dt7(Point(xoffset + 6*xscale, ymax-yoffset+20),dt[6]);
        win2.attach(dt1);win2.attach(dt2);win2.attach(dt3);
        win2.attach(dt4);win2.attach(dt5);win2.attach(dt6);
        win2.attach(dt7);

        win2.wait_for_button();
        return 0;
        }
        
        
        //图像绘制-预测数据折线-8月末
        if(is_head){
        vector<string> d_bef;
        d_bef.push_back("08-29");d_bef.push_back("08-30");d_bef.push_back("08-31");
        int mark_head = data_x[0]-4;
        for(int i = 0; i < weekday-1; i++){                 //以全体数据为源,给出 n=2 的拉格朗日估计
            w_data.insert({d_bef[i],Distribution(d_bef[i],
            int(lagrange(data_x,data_yhigh,mark_head+i,2)),
            int(lagrange(data_x,data_ylow,mark_head+i,2)))});
        }   
        map<string, Distribution>::iterator g_dayb = w_data.begin();
        Open_polyline high_t, low_t;
        Open_polyline high_tb, low_tb;
        vector<string> dt;
        for(int i = 1; i <= weekday; i++){
            high_tb.add(Point(xoffset + (i-1)*xscale, 
                ymax-yoffset-(g_dayb->second.h_tem)*yscale+10));
            low_tb.add(Point(xoffset + (i-1)*xscale, 
                ymax-yoffset-(g_dayb->second.l_tem)*yscale+5));
                dt.push_back(g_dayb->second.date);
                g_dayb++;
        }
        for(int i = weekday; i <= 7; i++){
            high_t.add(Point(xoffset + (i-1)*xscale, 
                ymax-yoffset-(g_dayb->second.h_tem)*yscale));
            low_t.add(Point(xoffset + (i-1)*xscale, 
                ymax-yoffset-(g_dayb->second.l_tem)*yscale+5));
                dt.push_back(g_dayb->second.date);
                g_dayb++;
        }
        high_t.set_style(Line_style::solid);
        high_t.set_color(Color::dark_red);
        low_t.set_style(Line_style::solid);
        low_t.set_color(Color::dark_blue);
        high_tb.set_style(Line_style::dot);
        high_tb.set_color(Color::dark_red);
        low_tb.set_style(Line_style::dot);
        low_tb.set_color(Color::dark_blue);
        win2.attach(high_tb);
        win2.attach(low_tb);
        win2.attach(high_t);
        win2.attach(low_t);

        //日期标签绘制
        Text dt1(Point(xoffset, ymax-yoffset+20),dt[0]);
        Text dt2(Point(xoffset + xscale, ymax-yoffset+20),dt[1]);
        Text dt3(Point(xoffset + 2*xscale, ymax-yoffset+20),dt[2]);
        Text dt4(Point(xoffset + 3*xscale, ymax-yoffset+20),dt[3]);
        Text dt5(Point(xoffset + 4*xscale, ymax-yoffset+20),dt[4]);
        Text dt6(Point(xoffset + 5*xscale, ymax-yoffset+20),dt[5]);
        Text dt7(Point(xoffset + 6*xscale, ymax-yoffset+20),dt[6]);
        win2.attach(dt1);win2.attach(dt2);win2.attach(dt3);
        win2.attach(dt4);win2.attach(dt5);win2.attach(dt6);
        win2.attach(dt7);

        win2.wait_for_button();
        }

        //图像绘制-预测数据折线-11月初
        if(is_tail){
        vector<string> d_bef;
        d_bef.push_back("11-01");d_bef.push_back("11-02");d_bef.push_back("11-03");
        d_bef.push_back("11-04");d_bef.push_back("11-05");d_bef.push_back("11-06");
        int mark_tail = data_x[60] + 1;
        for(int i = weekday-1; i < 6; i++){                 //以全体数据为源,给出 n=1 的拉格朗日估计
            w_data.insert({d_bef[i],Distribution(d_bef[i],
            int(lagrange(data_x,data_yhigh,mark_tail+i,1)),
            int(lagrange(data_x,data_ylow,mark_tail+i,1)))});
        } 
        map<string, Distribution>::iterator g_dayb = w_data.find(give_date);
        Open_polyline high_t, low_t;
        Open_polyline high_tb, low_tb;
        vector<string> dt;
        for(int i = weekday; i <= 7; i++){
            high_t.add(Point(xoffset + (i-1)*xscale, 
                ymax-yoffset-(g_dayb->second.h_tem)*yscale));
            low_t.add(Point(xoffset + (i-1)*xscale, 
                ymax-yoffset-(g_dayb->second.l_tem)*yscale+5));
                dt.push_back(g_dayb->second.date);
                if(g_dayb != w_data.end())g_dayb++;
        }
        high_t.set_style(Line_style::dot);
        high_t.set_color(Color::dark_red);
        low_t.set_style(Line_style::dot);
        low_t.set_color(Color::dark_blue);
        win2.attach(high_t);
        win2.attach(low_t);

        //日期标签绘制
        Text dt1(Point(xoffset, ymax-yoffset+20),dt[0]);
        Text dt2(Point(xoffset + xscale, ymax-yoffset+20),dt[1]);
        Text dt3(Point(xoffset + 2*xscale, ymax-yoffset+20),dt[2]);
        Text dt4(Point(xoffset + 3*xscale, ymax-yoffset+20),dt[3]);
        Text dt5(Point(xoffset + 4*xscale, ymax-yoffset+20),dt[4]);
        Text dt6(Point(xoffset + 5*xscale, ymax-yoffset+20),dt[5]);
        Text dt7(Point(xoffset + 6*xscale, ymax-yoffset+20),dt[6]);
        win2.attach(dt1);win2.attach(dt2);win2.attach(dt3);
        win2.attach(dt4);win2.attach(dt5);win2.attach(dt6);
        win2.attach(dt7);

        win2.wait_for_button();
        }
    }
}
