
#ifndef RUNGEKUTT_H
#define RUNGEKUTT_H

#include <vector>
#include <functional>
#include <iostream>

#include "BaseMethod.h"

class RungeKutt : public BaseMethod{

public:

    RungeKutt() {
        p = 4;
    }

    void Execute(double h, double t_start, double t_finish, const std::vector<double>& x_start_vec,
               const std::vector<std::function<double(double, const std::vector<double>&)>>& functions, double eps) override {
        std::vector<double> x_current_vec = x_start_vec;
        double t_current = t_start;
        do {
            x_result_vecs.push_back(x_current_vec);
            t_result_vec.push_back(t_current);
            x_current_vec = richardson(h, t_current, x_current_vec, functions, eps);
            t_current += h;
        } while(t_current < t_finish);
    }

private:

    std::vector<double> calc_next_vec(double h, double t_current, const std::vector<double>& x_current_vec,
                                      const std::vector<std::function<double(double, const std::vector<double>&)>>& functions) override {

        std::vector<double> x_next_vec(x_current_vec.size());
        auto nu1 = this->nu1(h, t_current, x_current_vec, functions);
        auto nu2 = this->nu2(h, t_current, nu1, x_current_vec, functions);
        auto nu3 = this->nu3(h, t_current, nu2, x_current_vec, functions);
        auto nu4 = this->nu4(h, t_current, nu3, x_current_vec, functions);
        right_part_calc_count += 4;
        for(std::size_t i = 0; i < x_current_vec.size(); ++i) {
            x_next_vec[i] = x_current_vec[i] + (nu1[i] + 2 * nu2[i] + 2 * nu3[i] + nu4[i]) / 6;
        }
        return x_next_vec;
    }

    std::vector<double> nu1(double h, double t, const std::vector<double>& x_vec,
                const std::vector<std::function<double(double, const std::vector<double>&)>>& functions) {
        std::vector<double> nu1(x_vec.size());
        for(std::size_t i = 0; i < x_vec.size(); ++i)  {
            nu1[i] = h * functions[i](t, x_vec);
        }
        return nu1;
    }

    std::vector<double> nu2(double h, double t, const std::vector<double>& nu1, const std::vector<double>& x_vec,
                const std::vector<std::function<double(double, const std::vector<double>&)>>& functions) {

        std::vector<double> x_vec_new(x_vec.size());
        for(std::size_t i = 0; i < x_vec.size(); ++i) {
            x_vec_new[i] = x_vec[i] + nu1[i] / 2;
        }
        std::vector<double> nu2(x_vec.size());
        for(std::size_t i = 0; i < x_vec.size(); ++i) {
            nu2[i] = h * functions[i](t + h / 2, x_vec_new);
        }
        return nu2;
    }

    std::vector<double> nu3(double h, double t, const std::vector<double>& nu2, const std::vector<double>& x_vec,
                const std::vector<std::function<double(double, const std::vector<double>&)>>& functions) {

        std::vector<double> x_vec_new(x_vec.size());
        for(std::size_t i = 0; i < x_vec.size(); ++i) {
            x_vec_new[i] = x_vec[i] + nu2[i] / 2;
        }
        std::vector<double> nu3(x_vec.size());
        for(std::size_t i = 0; i < x_vec.size(); ++i) {
            nu3[i] = h * functions[i](t + h / 2, x_vec_new);
        }
        return nu3;
    }

    std::vector<double> nu4(double h, double t, const std::vector<double>& nu3, const std::vector<double>& x_vec,
                const std::vector<std::function<double(double, const std::vector<double>&)>>& functions) {

        std::vector<double> x_vec_new(x_vec.size());
        for(std::size_t i = 0; i < x_vec.size(); ++i) {
            x_vec_new[i] = x_vec[i] + nu3[i];
        }
        std::vector<double> nu4(x_vec.size());
        for(std::size_t i = 0; i < x_vec.size(); ++i) {
            nu4[i] = h * functions[i](t + h, x_vec_new);
        }
        return nu4;
    }

};

#endif // RUNGEKUTT_H
