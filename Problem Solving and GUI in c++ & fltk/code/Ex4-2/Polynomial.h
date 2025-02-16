#ifndef INC_1_2_POLYNOMIAL_H
#define INC_1_2_POLYNOMIAL_H

#endif //INC_1_2_POLYNOMIAL_H

float conversion(float input,int potnum);
class Polynomial;
void divsion(Polynomial* A,Polynomial* B,Polynomial* res);
class Polynomial{
    friend void divsion(Polynomial* A,Polynomial* B,Polynomial* res);
private:
    static const int N = 30;
    double x[N];
public:
    Polynomial(char* str, bool &isarror);
    Polynomial();
    int maxpow();
    void Out_Sta();
    bool iszero();
    double Solve(double t);
};
