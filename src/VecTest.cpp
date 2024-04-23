#include <iostream>
#include "Eiler.h"
#include "Runge-Kutt.h"
#include <cmath>
#include <algorithm>
#include "switcher.h"
#include "Kutta-Mersen.h"
#include "RungeKuttImpl.h"
#include "EilerImplicitAnyDim.h"
#include "cmath"

#ifdef vecttest
#define RUNGE

int main()
{
    std::vector<std::function<double(double, const std::vector<double>&)>> F{
        [](double t, const std::vector<double>& x){
            return x[1];
        },
        [](double t, const std::vector<double>& x) {
            return -x[0];
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
            [](double t, const std::vector<double>& x){
                  return -1;
            },
            [](double t, const std::vector<double>& x){
                  return 0;
            },
        }
    };
    double h = 1e-3; //Шаг метода
    double t_start = 0.0; //Стартовая точка
    double t_finish = 10.0; //Конечная точка
    double eps = 1e-6; //Точность
    std::vector<double> x_start_vec{1.0, 1.0}; //x(0) = 1, x'(0) = 1

    #ifdef RUNGE
    RungeKuttImpl method{{1.0/3, 1.0}, {{5.0/12, -1.0/12}, {3.0/4, 1.0/4}}, {3.0/4, 1.0/4}};
    // double sqr = std::sqrt(6.0);
    // RungeKuttImpl method{{(4 - sqr)/10, (4 + sqr)/10, 1.0},
    //                         {{(88 - 7*sqr)/360, (296 - 169*sqr)/1800, (-2 + 3*sqr)/225},
    //                         {(296 + 169*sqr)/1800, (88 + 7*sqr)/360, (-2 - 3*sqr)/225},
    //                         {(16 - sqr)/36, (16 + sqr)/36, 1.0/9}}, 
    //                         {(16 - sqr)/36, (16 + sqr)/36, 1.0/9}};
    #endif
    #ifdef EILER
    EilerImplicitAnyDim method;
    #endif
    method.Execute(h, t_start, t_finish, x_start_vec, F, J, 1e-3);

    auto x_vecs_result = method.get_x_result_vecs();
    auto t_vec_result = method.get_t_result_vec();


    std::vector<std::function<double(double)>> answers(2); // Точное решение
    answers[0] = [](double t){
        return std::sin(t) + std::cos(t);
    };

    answers[1] = [](double t){
        return -std::sin(t) + std::cos(t);
    };

    std::vector<std::vector<double>> x_vecs_result_answer{t_vec_result.size()};

    for(std::size_t i = 0; i < x_vecs_result_answer.size(); ++i) {
        x_vecs_result_answer[i] = std::vector<double>(2);
        x_vecs_result_answer[i][0] = answers[0](t_vec_result[i]);
        x_vecs_result_answer[i][1] = answers[1](t_vec_result[i]);
    }

    std::vector<std::vector<double>> error_vec(x_vecs_result.size());
    for(std::size_t i = 0; i < error_vec.size(); ++i) {
        error_vec[i] = std::vector<double>(2);
        error_vec[i][0] = std::abs(x_vecs_result[i][0] - x_vecs_result_answer[i][0]);
        error_vec[i][1] = std::abs(x_vecs_result[i][1] - x_vecs_result_answer[i][1]);
    }

    std::vector<double> norms(error_vec.size());
    for(std::size_t i = 0; i < norms.size(); ++i) {
        norms[i] = std::max(error_vec[i][0], error_vec[i][1]);
    }

    std::cout << *std::max_element(norms.begin(), norms.end()) << "\n\n";

    return 0;
}

#endif
