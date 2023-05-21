#include "mainwindow.h"
#include <QApplication>
#include "Eiler.h"
#include "Runge-Kutt.h"
#include "Kutta-Mersen.h"
#include <QVector>
#include <iostream>
#include "switcher.h"

#ifndef test


int main(int argc, char *argv[])
{
    double zeta = 0.5;
    double omega = 1;
    std::vector<std::function<double(double, const std::vector<double>&)>> functions(2);
    functions[0] = [](double t, const std::vector<double>& x_vec){
        return x_vec[1];
    };
    functions[1] = [zeta, omega](double t, const std::vector<double>& x_vec) {
        return -2 * zeta * omega * x_vec[1] - omega * omega * x_vec[0];
    };
    double h = 0.001;
    double t_start = 0.0;
    double t_finish = 100;
    std::vector<double> x_start_vec{15.0, 15.0};
    double eps = 0.000001;
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
    method.Execute(h, t_start, t_finish, x_start_vec, functions, eps, true);
    auto x_vecs_result = method.get_x_result_vecs();
    auto t_vec_result = method.get_t_result_vec();
    auto step_div_vec = method.get_div_vec();
    auto step_doubling_vec = method.get_doubling_vec();
    auto step_divide_counter = method.get_step_divide_count();
    auto step_doubling_counter = method.get_step_doubling_count();
    std::cout << "Div: " << step_divide_counter <<
                 "  Double: " << step_doubling_counter << " Right part count: " << method.get_right_part_calc_count();
    QVector<double> t, x1, x2;
    QVector<std::size_t> div, doubling;

    //std::cout << "\n" << x_vecs_result.size() << " " << t_vec_result.size() << " " << step_div_vec.size() << " " << step_doubling_vec.size();
    for(std::size_t i = 0; i < t_vec_result.size(); ++i) {
        t.push_back(t_vec_result[i]);
        x1.push_back(x_vecs_result[i][0]);
        x2.push_back(x_vecs_result[i][1]);
        div.push_back(step_div_vec[i]);
        doubling.push_back(step_doubling_vec[i]);
    }

//    std::cout << x1.size();
    QApplication a(argc, argv);
    MainWindow w;
    w.CreateTable(t, x1, x2, div, doubling);
    w.Maketx1(t, x1);
    w.Maketx2(t, x2);
    w.Makex1x2(x1, x2);
    w.show();
    return a.exec();
    return 0;
}

#endif
