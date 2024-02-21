/*
std_lib_facilities.h
*/

/*
simple "Programming: Principles and Practice using C++ (second edition)" course header to
be used for the first few weeks.
It provides the most common standard headers (in the global namespace)
and minimal exception/error support.

Students: please don't try to understand the details of headers just yet.
All will be explained. This header is primarily used so that you don't have
to understand every concept all at once.

By Chapter 10, you don't need this file and after Chapter 21, you'll understand it

Revised April 25, 2010: simple_error() added

Revised November 25 2013: remove support for pre-C++11 compilers, use C++11: <chrono>
Revised November 28 2013: add a few container algorithms
Revised June 8 2014: added #ifndef to workaround Microsoft C++11 weakness
Revised Febrary 2 2015: randint() can now be seeded (see exercise 5.13).
Revised August 3, 2020: a cleanup removing support for ancient compilers
*/

#ifndef H112
#define H112 080315L


#include<iostream>
#include<iomanip>
#include<fstream>
#include<sstream>
#include<cmath>
#include<cstdlib>
#include<string>
#include<list>
#include <forward_list>
#include<vector>
#include<unordered_map>
#include<algorithm>
#include <array>
#include <regex>
#include<random>
#include<stdexcept>

//------------------------------------------------------------------------------


typedef long Unicode;

//------------------------------------------------------------------------------

using namespace std;

template<class T> string to_string(const T& t)
{
    ostringstream os;
    os << t;
    return os.str();
}

struct Range_error : out_of_range {	// enhanced vector range error reporting
    int index;
    Range_error(int i) :out_of_range("Range error: " + to_string(i)), index(i) { }
};


// trivially range-checked vector (no iterator checking):
template< class T> struct Vector : public std::vector<T> {
    using size_type = typename std::vector<T>::size_type;

/* #ifdef _MSC_VER
	// microsoft doesn't yet support C++11 inheriting constructors
	Vector() { }
	explicit Vector(size_type n) :std::vector<T>(n) {}
	Vector(size_type n, const T& v) :std::vector<T>(n, v) {}
	template <class I>
	Vector(I first, I last) : std::vector<T>(first, last) {}
	Vector(initializer_list<T> list) : std::vector<T>(list) {}
*/
    using std::vector<T>::vector;	// inheriting constructor

    T& operator[](unsigned int i) // rather than return at(i);
    {
        if (i<0 || this->size() <= i) throw Range_error(i);
        return std::vector<T>::operator[](i);
    }
    const T& operator[](unsigned int i) const
    {
        if (i<0 || this->size() <= i) throw Range_error(i);
        return std::vector<T>::operator[](i);
    }
};

// disgusting macro hack to get a range checked vector:
#define vector Vector

// trivially range-checked string (no iterator checking):
struct String : std::string {
    using size_type = std::string::size_type;
    //	using string::string;

    char& operator[](unsigned int i) // rather than return at(i);
    {
        if (i<0 || size() <= i) throw Range_error(i);
        return std::string::operator[](i);
    }

    const char& operator[](unsigned int i) const
    {
        if (i<0 || size() <= i) throw Range_error(i);
        return std::string::operator[](i);
    }
};


namespace std {

    template<> struct hash<String>
    {
        size_t operator()(const String& s) const
        {
            return hash<std::string>()(s);
        }
    };

} // of namespace std


struct Exit : runtime_error {
    Exit() : runtime_error("Exit") {}
};

// error() simply disguises throws:
inline void error(const string& s)
{
    throw runtime_error(s);
}

inline void error(const string& s, const string& s2)
{
    error(s + s2);
}

inline void error(const string& s, int i)
{
    ostringstream os;
    os << s << ": " << i;
    error(os.str());
}


template<class T> char* as_bytes(T& i)	// needed for binary I/O
{
    void* addr = &i;	// get the address of the first byte
    // of memory used to store the object
    return static_cast<char*>(addr); // treat that memory as bytes
}


inline void keep_window_open()
{
    cin.clear();
    cout << "Please enter a character to exit\n";
    char ch;
    cin >> ch;
    return;
}

inline void keep_window_open(string s)
{
    if (s == "") return;
    cin.clear();
    cin.ignore(120, '\n');
    for (;;) {
        cout << "Please enter " << s << " to exit\n";
        string ss;
        while (cin >> ss && ss != s)
            cout << "Please enter " << s << " to exit\n";
        return;
    }
}



// error function to be used (only) until error() is introduced in Chapter 5:
inline void simple_error(string s)	// write ``error: s and exit program
{
    cerr << "error: " << s << '\n';
    keep_window_open();		// for some Windows environments
    exit(1);
}

// make std::min() and std::max() accessible on systems with antisocial macros:
#undef min
#undef max


// run-time checked narrowing cast (type conversion). See ???.
template<class R, class A> R narrow_cast(const A& a)
{
    R r = R(a);
    if (A(r) != a) error(string("info loss"));
    return r;
}

// random number generators. See 24.7.

inline default_random_engine& get_rand()
{
    static default_random_engine ran;	// note: not thread_local
    return ran;
};

inline void seed_randint(int s) { get_rand().seed(s); }

inline int randint(int min, int max) { return uniform_int_distribution<>{min, max}(get_rand()); }

inline int randint(int max) { return randint(0, max); }

//inline double sqrt(int x) { return sqrt(double(x)); }	// to match C++0x

// container algorithms. See 21.9.   // C++ has better versions of this:

template<typename C>
using Value_type = typename C::value_type;

template<typename C>
using Iterator = typename C::iterator;

template<typename C>
// requires Container<C>()
void sort(C& c)
{
    std::sort(c.begin(), c.end());
}

template<typename C, typename Pred>
// requires Container<C>() && Binary_Predicate<Value_type<C>>()
void sort(C& c, Pred p)
{
    std::sort(c.begin(), c.end(), p);
}

template<typename C, typename Val>
// requires Container<C>() && Equality_comparable<C,Val>()
Iterator<C> find(C& c, Val v)
{
    return std::find(c.begin(), c.end(), v);
}

template<typename C, typename Pred>
// requires Container<C>() && Predicate<Pred,Value_type<C>>()
Iterator<C> find_if(C& c, Pred p)
{
    return std::find_if(c.begin(), c.end(), p);
}

#endif //H112

#include <set>

stringstream ss;
stringstream ss_out;
multimap<string, string> take;
multimap<string, string> give;
set<string> name_ser;

struct Token {
    char kind;
    double value;
    string name;
    Token(char ch) :kind(ch), value(0) { }
    Token(char ch, double val) :kind(ch), value(val) { }
    Token(char ch, string na) :name(na), kind(ch), value(0){ }
};

class Token_stream {
    bool full;
    Token buffer;
public:
    Token_stream() :full(0), buffer(0) { }

    Token get();
    void unget(Token t) { buffer = t; full = true; }
    void clear() {full = false;}
    void ignore(char);
};

const char let = 'L';
const char quit = 'Q';
const char print = ';';
const char number = '8';
const char name = 'a';

Token Token_stream::get()
{
    if (full) { full = false; return buffer; }
    char ch;
    ss >> ch;
    switch (ch) {
        case '!':
        case '(':
        case ')':
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
        case ';':
        case '=':
            return Token(ch);
        case '.':
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        {	ss.unget();
            double val;
            ss >> val;
            return Token(number, val);
        }
        default:
            if (isalpha(ch)) {
                string s;
                s += ch;
                while (ss.get(ch) && (isalpha(ch) || isdigit(ch))) s += ch;
                ss.unget();
                if (s == "let") return Token(let);
                if (s == "quit") return Token(quit);
                return Token(name, s);
            }
            error("Bad token");
    }
}

void Token_stream::ignore(char c)
{
    if (full && c == buffer.kind) {
        full = false;
        return;
    }
    full = false;

    char ch;
    while (ss >> ch)
        if (ch == c) return;
}

struct Variable {
    string name;
    double value;
    Variable(string n, double v) :name(n), value(v) { }
};

vector<Variable> names;

double get_value(string s)
{
    for (int i = 0; i < names.size(); ++i)
        if (names[i].name == s) return names[i].value;
    error("get: undefined name ", s);
}

bool is_declared(string s)
{
    for (int i = 0; i < names.size(); ++i)
        if (names[i].name == s) return true;
    return false;
}

Token_stream ts;

double expression();

bool is_valid_int(double a){
    int b = a;
    double c = b;
    if((abs(a-c) <= 1e-6) && a >= 0)return true;
    else return false;
}

double factorial(int k){
    double result = 1;
    for(int i = 2; i <= k; i++){
        result *= i;
    }
    return result;
}

double primary()
{
    Token t = ts.get();
    switch (t.kind) {
        case '(':
        {	double d = expression();
            t = ts.get();
            if (t.kind != ')') error("'(' expected");
            return d;
        }
        case number:
            return t.value;
        case name:
            return get_value(t.name);
        default:
            error("primary expected");
    }
}
double fact()
{
    Token t = ts.get();
    if(t.kind == '!') error("primary expected");
    else ts.unget(t);
    double left = primary();
    t = ts.get();
    switch (t.kind) {
        case '!':
        {   if (!is_valid_int(left)) error("!: invalid factorial");
            int k = left;
            left =  factorial(k);
            return left;
        }
        default:
            ts.unget(t);
            return left;
    }
}
double isnag()
{
    Token t = ts.get();
    switch (t.kind) {
        case '-':
            return -fact();
        default:
            ts.unget(t);
            return fact();
    }
}

double term()
{
    double left = isnag();
    while (true) {
        Token t = ts.get();
        switch (t.kind) {
            case '*':
                left *= isnag();
                break;
            case '/':
            {	double d = isnag();
                if (d == 0) error("divide by zero");
                left /= d;
                break;
            }
            default:
                ts.unget(t);
                return left;
        }
    }
}

double expression()
{
    double left = term();
    while (true) {
        Token t = ts.get();
        switch (t.kind) {
            case '+':
                left += term();
                break;
            case '-':
                left -= term();
                break;
            default:
                ts.unget(t);
                return left;
        }
    }
}

double declaration()
{
    Token t = ts.get();
    if (t.kind != 'a') error("name expected in declaration");
    string name = t.name;
    if (is_declared(name)) error(name, " declared twice");
    Token t2 = ts.get();
    if (t2.kind != '=') error("= missing in declaration of ", name);
    double d = expression();
    names.push_back(Variable(name, d));
    return d;
}

double statement()
{
    Token t = ts.get();
    switch (t.kind) {
        case let:
            return declaration();
        default:
            ts.unget(t);
            return expression();
    }
}

void clean_up_mess()
{
    ts.ignore(print);
}

const string result = "= ";

void calculate()
{
    while (true) try {
            Token t = ts.get();
            while (t.kind == print) {
                t = ts.get();
                return;
            }
            if (t.kind == quit) return;
            ts.unget(t);
            ss_out << statement() << ' ';
            ts.clear();
        }
        catch (runtime_error& e) {
            ss_out << 'w';
            clean_up_mess();
        }
}

//获取语句中的索引和算数式
void get_exp(string str_in){
    for(int i = 0; i < str_in.size(); i++){
        if(str_in[i] == 'q')return;
        if(str_in[i] == '['){
            i++;
            string mark;
            string expr;
            while (str_in[i] ==' '){
                i++;
            }
            while (str_in[i] != ']'){
                mark.push_back(str_in[i]);
                i++;
            }
            int j = i-1;
            while (str_in[j] == ' '){
                mark = mark.substr(0, mark.size()-1);
                j--;
            }
            i++;
            while (str_in[i] == ' ')i++;
            while (str_in[i] != ';'){
                expr.push_back(str_in[i]);
                i++;
            }
            int o = i-1;
            while (str_in[o] == ' '){
                expr = expr.substr(0, expr.size()-1);
                o--;
            }
            expr.push_back(';');
            expr.append("quit");
            //补丁
            i++;
            while (str_in[i] == ' '){
                i++;
            }
            if (str_in[i] != '[' && str_in[i] != 'q'){
                take.insert({mark,"w"});
                return;
            }
            i--;
            name_ser.insert(mark);
            take.insert({mark,expr});
        }
    }
}

int main(){
    string str1;
    string str2;
    getline(cin,str1);
    get_exp(str1);
    for(auto t: take){
        ss << t.second;
        try {
            if (ss.str() == "w")error("");
            calculate();
        }
        catch (exception& e) {
            ss_out << 'w';
            char c;
            while (ss >> c && c != ';');
        }
        catch (...) {
            ss_out << 'w';
            char c;
            while (ss >> c && c != ';');
        }
        if (ss_out.str() == "w"){
            t.second.clear();
        }
        ss.clear();
    }
    string last_fir = take.begin()->first;
    vector<string> so;
    for(auto t: take){
        char get_tmp;
        ss_out >> get_tmp;
        string out_str = "";
        if(get_tmp == 'w'){
            out_str = "w";
        }
        else {
            ss_out.putback(get_tmp);
            double result_num;
            ss_out >> result_num;
            out_str.append("=");
            stringstream change;
            change << result_num;
            string tmp;
            change >> tmp;
            out_str.append(tmp);
            out_str = t.second.substr(0,t.second.size()-5).append(out_str);
        }

        //键值内排序
        if (t.first == last_fir) {
            so.push_back(out_str);
            sort(so);
        }
        else{
            for(auto h: so){
                give.insert({last_fir,h});
            }
            so.clear();
            so.push_back(out_str);
        }
        last_fir = t.first;
    }
    for(auto h: so){
        give.insert({last_fir,h});
    }


    //输出环节
    string out_sign = "";
    getline(cin,out_sign);
    if(out_sign == ""){
        string last = "";
        for(auto t: give){
            if(t.first != last){
                cout << '[' << t.first << ']' << endl;
            }
            if (t.second.c_str()[0] == 'w'){
                t.second.clear();
                last = t.first;
                continue;
            }
            else cout << t.second << endl;
            last = t.first;
        }
    }
    else{
        if(out_sign[0] == ' ')out_sign = out_sign.substr(1);
        multimap<string,string>::iterator m;
        m = give.find(out_sign);
        if (m == give.end())cout << '[' << out_sign << ']' << endl;
        else {
            cout << '[' << m->first << ']' << endl;
            for (int k = 0; k != give.count(out_sign); k++,m++){
                if (m->second.c_str()[0] == 'w'){
                    m->second.clear();
                    continue;
                }
                else cout << m->second << endl;
            }
        }
    }
    return 0;
}


