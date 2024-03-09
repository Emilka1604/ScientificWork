#include "switcher.h"

#ifdef eilerimpl3on3any

#include "mainwindow.h"
#include <QApplication>
#include <QVector>
#include <iostream>

#include "EilerImplicitAnyDim.h"


int main(int argc, char *argv[])
{
    std::vector<std::function<double(double, const std::vector<double>&)>> F{
        [](double t, const std::vector<double>& x){
            return -0.04*x[0] + 1e4*x[1]*x[2];;
        },
        [](double t, const std::vector<double>& x) {
            return 0.04*x[0]-1e4*x[1]*x[2]-3*1e7*x[1]*x[1];
        },
        [](double t, const std::vector<double>& x) {
            return 3*1e7*x[1]*x[1];
        }
    };
    std::vector<std::vector<std::function<double(double, const std::vector<double>&)>>> J{
        {
              [](double t, const std::vector<double>& x){
                    return -0.04;
              },
              [](double t, const std::vector<double>& x){
                    return 1e4*x[2];
              },
              [](double t, const std::vector<double>& x){
                    return 1e4*x[1];
              }
        },
        {
              [](double t, const std::vector<double>& x){
                    return 0.04;
              },
              [](double t, const std::vector<double>& x){
                    return -1e4*x[2]-6*1e7*x[1];
              },
              [](double t, const std::vector<double>& x){
                    return -1e4*x[1];
              }
        },
        {
              [](double t, const std::vector<double>& x){
                    return 0.0;
              },
              [](double t, const std::vector<double>& x){
                    return 6*1e7*x[1];
              },
              [](double t, const std::vector<double>& x){
                    return 0.0;
              }
        }
    };
    double h = 1e-3;
    double t_start = 0.0;
    double t_finish = 0.3;
    std::vector<double> x_start_vec{1.0, 0.0, 0.0};
    EilerImplicitAnyDim method;
    method.Execute(h, t_start, t_finish, x_start_vec, F, J, 1e-6);
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
