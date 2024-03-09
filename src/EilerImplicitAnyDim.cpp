#include "switcher.h"

#ifdef eilerimplany2on2

#include "EilerImplicitAnyDim.h"

#include "mainwindow.h"
#include <QApplication>
#include <QVector>
#include <iostream>


int main(int argc, char *argv[])
{
    double nu = 500.0;

    std::vector<std::function<double(double, const std::vector<double>&)>> F{
        [](double t, const std::vector<double>& x){
            return x[1];
        },
        [nu](double t, const std::vector<double>& x) {
            return nu*(1-x[0]*x[0])*x[1]-x[0];
        }
    };

    std::vector<std::vector<std::function<double(double, const std::vector<double>&)>>> J{
        {
            [](double t, const std::vector<double>& x){
                  return 0;
            },
            [](double t, const std::vector<double>& x){
                  return 1;
            },
        },
        {
            [nu](double t, const std::vector<double>& x){
                  return -2*nu*x[0]*x[1] - 1;
            },
            [nu](double t, const std::vector<double>& x){
                  return nu*(1-x[0]*x[0]);
            },
        }
    };
    double h = 1e-3;
    double t_start = 0.0;
    double t_finish = 1e-2;
    std::vector<double> x_start_vec{2.0, 0.0};
    EilerImplicitAnyDim method;
    method.Execute(h, t_start, t_finish, x_start_vec, F, J, 1e-6);
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
    std::cout << method.getNumOfSteps();
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
