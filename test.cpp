#include <iostream>
#include "Eiler.h"
#include "Runge-Kutt.h"
#include <cmath>
#include <algorithm>
#include "switcher.h"

#ifdef test

//#define eiler

int main()
{
    BaseMethod* method;
#ifdef eiler
    method = new Eiler;
#else
    method = new RungeKutt;
#endif
    std::vector<std::function<double(double, const std::vector<double>&)>> functions(2); // Правые части уравнений системы
    functions[0] = [](double t, const std::vector<double>& x_vec){
        return x_vec[1];
    };
    functions[1] = [](double t, const std::vector<double>& x_vec) {
        return -x_vec[0];
    };
    double h = 0.001; //Шаг метода
    double t_start = 0; //Стартовая точка
    double t_finish = 1; //Конечная точка
    std::vector<double> x_start_vec{1, 1}; //x(0) = 1, x'(0) = 1

    method->Execute(h, t_start, t_finish, x_start_vec, functions); // Запуск функции

    auto x_vecs_result = method->get_x_result_vecs();
    auto t_vec_result = method->get_t_result_vec();


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
