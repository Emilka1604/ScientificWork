#include "switcher.h"

#ifdef scalartest

#include <iostream>
#include "Eiler.h"
#include "Runge-Kutt.h"
#include "EilerImplicit.h"
#include <cmath>
#include <algorithm>
#include "Kutta-Mersen.h"


int main()
{
#ifdef eiler
    Eiler method;
#else
    #ifdef runge
        RungeKutt method;
    #else
        #ifdef kutta
            KuttaMersen method;
        #else
            #ifdef eilerimpl
                EilerImplicit method;
            #endif
        #endif
    #endif
#endif
    std::vector<std::function<double(double, const std::vector<double>&)>> functions(1); // Правые части уравнений системы
    functions[0] = [](double t, const std::vector<double>& x_vec){
        return -100 * x_vec[0] + 100;
    };
    double h = 5e-2; //Шаг метода
    double t_start = 0.0; //Стартовая точка
    double t_finish = 0.5; //Конечная точка
    double eps = 1e-2; //Точность
    std::vector<double> x_start_vec{2.0}; //x(0) = 1, x'(0) = 1

    method.Execute(h, t_start, t_finish, x_start_vec, functions, eps, true); // Запуск функции

    auto x_vecs_result = method.get_x_result_vecs();
    auto t_vec_result = method.get_t_result_vec();


    std::function<double(double)> answer = [](double t){
        return 1 + std::exp(-100*t);
    };

    std::vector<double> x_vecs_result_answer(t_vec_result.size());

    for(std::size_t i = 0; i < x_vecs_result_answer.size(); ++i) {
        x_vecs_result_answer[i] = answer(t_vec_result[i]);
    }

    std::vector<double> error_vec(x_vecs_result.size());
    for(std::size_t i = 0; i < error_vec.size(); ++i) {
        error_vec[i] = std::abs(x_vecs_result[i][0] - x_vecs_result_answer[i]);
    }

//    std::vector<double> norms(error_vec.size());
//    for(std::size_t i = 0; i < norms.size(); ++i) {
//        norms[i] = std::max(error_vec[i][0], error_vec[i][1]);
//    }

    std::cout << *std::max_element(error_vec.begin(), error_vec.end()) << "\n\n";
    std::cout << method.get_right_part_calc_count() << "\n\n";

    return 0;
}

#endif

