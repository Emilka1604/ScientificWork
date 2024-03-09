#include "switcher.h"

#ifdef eilerimpl

#include "mainwindow.h"
#include <QApplication>
#include "EilerImplicit.h"
#include <QVector>
#include <iostream>
#include <math.h>


int main(int argc, char *argv[])
{
    auto f = [](double h, double t, double x){
        return (x + 50*h*cos(t+h))/(1 + 50*h);
    };
    double h = 1.974/50;
    double t_start = 0.0;
    double t_finish = 0.12;
    double x_start = 0.0;
    EilerImplicit method;
    method.Execute(h, t_start, t_finish, x_start, f);
    auto x_vecs_result = method.get_x_result_vecs();
    auto t_vec_result = method.get_t_result_vec();
    auto step_vec = method.get_step_vec();
    QVector<double> h_vec, t, x1;
    for(std::size_t i = 0; i < t_vec_result.size(); ++i) {
        h_vec.push_back(step_vec[i]);
        t.push_back(t_vec_result[i]);
        x1.push_back(x_vecs_result[i]);
    }
    QApplication a(argc, argv);
    MainWindow w;
    w.CreateTable(h_vec, t, x1);
    w.Maketx1(t, x1);
    w.show();
    return a.exec();
    return 0;
}

#endif
