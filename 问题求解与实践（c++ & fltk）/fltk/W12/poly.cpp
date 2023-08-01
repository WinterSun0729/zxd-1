#include "poly.h"
#include "Graph.h"
bool is_a_polygon = true;

inline pair<double,double> line_intersect(Point p1, Point p2, Point p3, Point p4, bool& parallel)
{
    double x1 = p1.x;
    double x2 = p2.x;
    double x3 = p3.x;
    double x4 = p4.x;
    double y1 = p1.y;
    double y2 = p2.y;
    double y3 = p3.y;
    double y4 = p4.y;

    double denom = ((y4 - y3)*(x2-x1) - (x4-x3)*(y2-y1));
    if (denom == 0){
        parallel= true;
        return pair<double,double>(0,0);
    }
    parallel = false;
    return pair<double,double>( ((x4-x3)*(y1-y3) - (y4-y3)*(x1-x3))/denom,
                                ((x2-x1)*(y1-y3) - (y2-y1)*(x1-x3))/denom);
}

bool line_segment_intersect(Point p1, Point p2, Point p3, Point p4, Point& intersection){
   bool parallel;
   pair<double,double> u = line_intersect(p1,p2,p3,p4,parallel);
   if (parallel || u.first < 0 || u.first > 1 || u.second < 0 || u.second > 1) return false;
   intersection.x = p1.x + u.first*(p2.x - p1.x);
   intersection.y = p1.y + u.first*(p2.y - p1.y);
   return true;
}


void Poly::add(Point p)
{
    int np = number_of_points();

    if (1<np) {    // check that thenew line isn't parallel to the previous one
        if (p==point(np-1)) is_a_polygon = false;
        bool parallel;
        line_intersect(point(np-1),p,point(np-2),point(np-1),parallel);
        if (parallel)
            is_a_polygon = false;
    }

    for (int i = 1; i<np-1; ++i) {    // check that new segment doesn't interset and old point
        Point ignore(0,0);
        if (line_segment_intersect(point(np-1),p,point(i-1),point(i),ignore))
            is_a_polygon = false;
    }
    Closed_polyline::add(p);
}
void Poly::draw_lines() const
{
    if (number_of_points() < 3) is_a_polygon = false;
    Closed_polyline::draw_lines();
}

Poly_Win::Poly_Win(Point xy, int w, int h, const string& title)
:Window(xy,w,h,title),
next_button(Point(x_max()-230,0), 70, 20, "Next point", cb_next),
show_button(Point(x_max()-150,0), 70, 20, "Show", cb_show),
quit_button(Point(x_max()-70,0), 70, 20, "Quit", cb_quit),
next_x(Point(50,0), 50, 20, "next x:"),
next_y(Point(150,0), 50, 20, "next y:"),
is_poly(Point(310,0), 50, 20, "is a polygon?:"){
attach(next_button);
attach(show_button);
attach(quit_button); attach(next_x); attach(next_y); attach(is_poly);
}

void Poly_Win::cb_quit(Address, Address pw){reference_to<Poly_Win>(pw).quit();}
void Poly_Win::cb_next(Address, Address pw){reference_to<Poly_Win>(pw).next();}
void Poly_Win::cb_show(Address, Address pw){reference_to<Poly_Win>(pw).show();}

void Poly_Win::next(){
    int x = next_x.get_int();
    int y = next_y.get_int();
    points.push_back(Point(x,y));

    redraw();
}
void Poly_Win::show(){
    for(auto t:points){
        poly.add(t);
    }
    stringstream ss;
    if(is_a_polygon)ss << "No";
    else ss << "yes";
    is_poly.put(ss.str());
    Simple_window win(Point(0,0),600,400,"Show");
    win.attach(poly);
    win.wait_for_button();
}
void Poly_Win::quit(){hide();}