#include "switcher.h"

#ifdef newtontest

#include "Newton.h"

int main() {
    std::function<double(double, double, double)> f1 = [](double x1, double x2, double x3){
        return x1*x2+x2*x3+x1*x3+19;
    };
    std::function<double(double, double, double)> f2 = [](double x1, double x2, double x3){
        return x1*x1+x2*x2+2*x3*x3-63;
    };
    std::function<double(double, double, double)> f3 = [](double x1, double x2, double x3){
        return x1/(2*x2) + x2/(2*x1) - 13/12;
    };
    std::function<double(double, double, double)> df1dx = [](double x1, double x2, double x3){
        return x2+x3;
    };
    std::function<double(double, double, double)> df1dy = [](double x1, double x2, double x3){
        return x1+x3;
    };
    std::function<double(double, double, double)> df1dz = [](double x1, double x2, double x3){
        return x2+x1;
    };
    std::function<double(double, double, double)> df2dx = [](double x1, double x2, double x3){
        return 2*x1;
    };
    std::function<double(double, double, double)> df2dy = [](double x1, double x2, double x3){
        return 2*x2;
    };
    std::function<double(double, double, double)> df2dz = [](double x1, double x2, double x3){
        return -1e4*x2;
    };
    std::function<double(double, double, double)> df3dx = [](double x1, double x2, double x3){
        return 0.0;
    };
    std::function<double(double, double, double)> df3dy = [](double x1, double x2, double x3){
        return 6*1e7*x2;
    };
    std::function<double(double, double, double)> df3dz = [](double x1, double x2, double x3){
        return 0.0;
    };
    NewtonMethod nm;
    nm.newton3on3();
    return 0;
}

#endif
