#include "switcher.h"

#ifdef eilerimpl2on2

#include "mainwindow.h"
#include <QApplication>
#include <QVector>
#include <iostream>

#include "EilerImplicit2on2.h"


int main(int argc, char *argv[])
{
    double nu = 500.0;
    std::function<double(double, double, double)> f1 = [](double t, double x1, double x2){
        return x2;
    };
    std::function<double(double, double, double)> f2 = [nu](double t, double x1, double x2){
        return nu*(1-x1*x1)*x2-x1;
    };
    std::function<double(double, double, double)> df1dx = [](double t, double x1, double x2){
        return 0;
    };
    std::function<double(double, double, double)> df1dy = [](double t, double x1, double x2){
        return 1;
    };
    std::function<double(double, double, double)> df2dx = [nu](double t, double x1, double x2){
        return -2*nu*x1*x2 - 1;
    };
    std::function<double(double, double, double)> df2dy = [nu](double t, double x1, double x2){
        return nu*(1-x1*x1);
    };
    double h = 0.001;
    double t_start = 0.0;
    double t_finish = 0.01;
    std::vector<double> x_start_vec{2.0, 0.0};
    EilerImplicit2on2 method;
    method.Execute(h, t_start, t_finish, x_start_vec, f1, f2, df1dx, df1dy, df2dx, df2dy);
    auto x_vecs_result = method.get_x_result_vecs();
    auto t_vec_result = method.get_t_result_vec();
    auto step_vec = method.get_step_vec();
    QVector<double> h_vec, t, x1, x2;

    for(std::size_t i = 0; i < t_vec_result.size(); ++i) {
        h_vec.push_back(step_vec[i]);
        t.push_back(t_vec_result[i]);
        x1.push_back(x_vecs_result[i][0]);
        x2.push_back(x_vecs_result[i][1]);
    }

    QApplication a(argc, argv);
    MainWindow w;
    w.CreateTable(h_vec, t, x1, x2);
    w.Maketx1(t, x1);
    w.Maketx2(t, x2);
    w.Makex1x2(x1, x2);
    w.show();
    //std::cout << "end";
    return a.exec();
    return 0;
}

#endif
