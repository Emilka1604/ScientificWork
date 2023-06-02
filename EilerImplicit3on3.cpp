#include "switcher.h"

#ifdef eilerimpl3on3

#include "mainwindow.h"
#include <QApplication>
#include <QVector>
#include <iostream>

#include "EilerImplicit3on3.h"


int main(int argc, char *argv[])
{
    std::function<double(double, double, double, double)> f1 = [](double t, double x1, double x2, double x3){
        return -0.04*x1 + 1e4*x2*x3;
    };
    std::function<double(double, double, double, double)> f2 = [](double t, double x1, double x2, double x3){
        return 0.04*x1-1e4*x2*x3-3*1e7*x2*x2;
    };
    std::function<double(double, double, double, double)> f3 = [](double t, double x1, double x2, double x3){
        return 3*1e7*x2*x2;
    };
    std::function<double(double, double, double, double)> df1dx = [](double t, double x1, double x2, double x3){
        return -0.04;
    };
    std::function<double(double, double, double, double)> df1dy = [](double t, double x1, double x2, double x3){
        return 1e4*x3;
    };
    std::function<double(double, double, double, double)> df1dz = [](double t, double x1, double x2, double x3){
        return 1e4*x2;
    };
    std::function<double(double, double, double, double)> df2dx = [](double t, double x1, double x2, double x3){
        return 0.04;
    };
    std::function<double(double, double, double, double)> df2dy = [](double t, double x1, double x2, double x3){
        return -1e4*x3-6*1e7*x2;
    };
    std::function<double(double, double, double, double)> df2dz = [](double t, double x1, double x2, double x3){
        return -1e4*x2;
    };
    std::function<double(double, double, double, double)> df3dx = [](double t, double x1, double x2, double x3){
        return 0.0;
    };
    std::function<double(double, double, double, double)> df3dy = [](double t, double x1, double x2, double x3){
        return 6*1e7*x2;
    };
    std::function<double(double, double, double, double)> df3dz = [](double t, double x1, double x2, double x3){
        return 0.0;
    };
    double h = 1e-3;
    double t_start = 0.0;
    double t_finish = 0.3;
    std::vector<double> x_start_vec{1.0, 0.0, 0.0};
    EilerImplicit3on3 method;
    method.Execute(h, t_start, t_finish, x_start_vec, f1, f2, f3, df1dx, df1dy, df1dz, df2dx, df2dy, df2dz, df3dx, df3dy, df3dz, 1e-6);
    auto x_vecs_result = method.get_x_result_vecs();
    auto t_vec_result = method.get_t_result_vec();
    auto step_vec = method.get_step_vec();
    QVector<double> h_vec, t, x1, x2, x3;
    for(std::size_t i = 0; i < t_vec_result.size(); ++i) {
        h_vec.push_back(step_vec[i]);
        t.push_back(t_vec_result[i]);
        x1.push_back(x_vecs_result[i][0]);
        x2.push_back(x_vecs_result[i][1]);
        x3.push_back(x_vecs_result[i][2]);
    }
    std::cout << method.getNumOfSteps();
    QApplication a(argc, argv);
    MainWindow w;
    w.CreateTable(h_vec, t, x1, x2, x3);
    w.Maketx1(t, x1);
    w.Maketx2(t, x2);
    w.Maketx3(t, x3);
    w.show();
    //std::cout << "end";
    return a.exec();
    return 0;
}

#endif
