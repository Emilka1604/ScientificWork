#include "switcher.h"

#ifdef expl2on2

#include "mainwindow.h"
#include <QApplication>
#include "Eiler.h"
#include "Runge-Kutt.h"
#include "Kutta-Mersen.h"
#include <QVector>
#include <iostream>


int main(int argc, char *argv[])
{
    double nu = 500;
    std::vector<std::function<double(double, const std::vector<double>&)>> functions(2);
    functions[0] = [](double t, const std::vector<double>& x_vec){
        return x_vec[1];
    };
    functions[1] = [nu](double t, const std::vector<double>& x_vec) {
        return nu * (1-x_vec[0]*x_vec[0]) * x_vec[1] - x_vec[0];
    };
    double h = 1e-3;
    double t_start = 0.0;
    double t_finish = 1e-2;
    std::vector<double> x_start_vec{2.0, 0.0};
    double eps = 1e-6;
#ifdef eiler
    Eiler method;
#else
    #ifdef runge
        RungeKutt method;
    #else
        #ifdef kutta
            KuttaMersen method;
        #endif
    #endif
#endif
    bool isDoubling = true;
    method.Execute(h, t_start, t_finish, x_start_vec, functions, eps, isDoubling);
    auto x_vecs_result = method.get_x_result_vecs();
    auto t_vec_result = method.get_t_result_vec();
    auto step_div_vec = method.get_div_vec();
    auto step_doubling_vec = method.get_doubling_vec();
    auto step_vec = method.get_step_vec();
    auto step_divide_counter = method.get_step_divide_count();
    auto step_doubling_counter = method.get_step_doubling_count();
    auto right_part_calc_count = method.get_right_part_calc_count();
    QVector<double> h_vec, t, x1, x2;
    QVector<std::size_t> div, doubling;

    for(std::size_t i = 0; i < t_vec_result.size(); ++i) {
        h_vec.push_back(step_vec[i]);
        t.push_back(t_vec_result[i]);
        x1.push_back(x_vecs_result[i][0]);
        x2.push_back(x_vecs_result[i][1]);
        if(isDoubling) {
            div.push_back(step_div_vec[i]);
            doubling.push_back(step_doubling_vec[i]);
        }
    }

    QApplication a(argc, argv);
    MainWindow w;
    if(isDoubling) {
        w.CreateTable(h_vec, t, x1, x2, div, doubling);
    } else {
        w.CreateTable(h_vec, t, x1, x2);
    }
    w.Maketx1(t, x1);
    w.Maketx2(t, x2);
    w.Makex1x2(x1, x2);
    w.MakeStepPlot(t, h_vec);
    w.setDivide(step_divide_counter);
    w.setDoubling(step_doubling_counter);
    w.setRightPartCalc(right_part_calc_count);
    w.show();
    return a.exec();
    return 0;
}

#endif
