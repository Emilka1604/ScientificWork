#include "switcher.h"

#ifdef rungekuttimpl
#define THREEDIM

#include "RungeKuttImpl.h"

#include "mainwindow.h"
#include <QApplication>
#include <QVector>
#include <iostream>


int main(int argc, char *argv[])
{
    #ifdef TWODIM
    double nu = 100.0;

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
    double t_start = 0;
    double t_finish = 1e-2;
    std::vector<double> x_start_vec{2.0, 0.0};
    RungeKuttImpl method{{1.0/3, 1.0}, {{5.0/12, -1.0/12}, {3.0/4, 1.0/4}}, {3.0/4, 1.0/4}};
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
    w.MakeStepPlot(t, h_vec);
    std::cout << "end";
    #endif
    #ifdef THREEDIM
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
    RungeKuttImpl method{{1.0/3, 1.0}, {{5.0/12, -1.0/12}, {3.0/4, 1.0/4}}, {3.0/4, 1.0/4}};
    method.Execute(h, t_start, t_finish, x_start_vec, F, J, 1e-6);
    auto x_vecs_result = method.get_x_result_vecs();
    auto t_vec_result = method.get_t_result_vec();
    auto step_vec = method.get_step_vec();
    auto localErr = method.get_local_err();
    QVector<double> t, x1, x2, x3, h_vec, err;
    for(std::size_t i = 0; i < t_vec_result.size(); ++i) {
        x1.push_back(x_vecs_result[i][0]);
        x2.push_back(x_vecs_result[i][1]);
        x3.push_back(x_vecs_result[i][2]);
        t.push_back(t_vec_result[i]);
        h_vec.push_back(step_vec[i]);
        err.push_back(localErr[i]); 
    }
    std::cout << method.getNumOfSteps();
    QApplication a(argc, argv);
    MainWindow w;
    w.CreateTable(h_vec, t, x1, x2, x3, QVector<std::size_t>(t.size(), 0), QVector<std::size_t>(t.size(), 0), err);
    w.Maketx1(t, x1);
    w.Maketx2(t, x2);
    w.Maketx3(t, x3);
    w.MakeStepPlot(t, h_vec);
    w.MakeLocalErrPlot(t, err);
    #endif
    w.show();
    return a.exec();
    return 0;
}

#endif