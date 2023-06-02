#ifndef EILER_H
#define EILER_H

#include <vector>
#include <functional>
#include <math.h>
#include <algorithm>
#include <numeric>


class Eiler{

private:

    std::vector<std::vector<double>> x_result_vecs;
    std::vector<double> t_result_vec;
    std::vector<std::size_t> div_vec;
    std::vector<std::size_t> doubling_vec;
    std::vector<double> step_vec;
    std::size_t right_part_calc_count{0};
    const std::size_t p = 1;

    std::vector<double> calc_next_vec(double h, double t_current, const std::vector<double>& x_current_vec,
                                      const std::vector<std::function<double(double, const std::vector<double>&)>>& functions){

        std::vector<double> x_next_vec(x_current_vec.size());
        for(std::size_t i = 0; i < x_current_vec.size(); ++i) {
            x_next_vec[i] = x_current_vec[i] + h * functions[i](t_current, x_current_vec);
        }
        ++right_part_calc_count;
        return x_next_vec;
    }

    auto richardson(double& h, double t_current, const std::vector<double>& x_current_vec,
                    const std::vector<std::function<double(double, const std::vector<double>&)>>& functions, double eps, bool& doubleStep) {
        double R = 0;
        std::vector<double> res_with_step;
        std::vector<double> half_step;
        std::vector<double> res_with_step_div_two;
        div_vec.push_back(0);
        doubling_vec.push_back(0);
        if(doubleStep) {
            h *= 2;
            ++doubling_vec[doubling_vec.size() - 1];
            doubleStep = false;
        }
        do {
            res_with_step = calc_next_vec(h, t_current, x_current_vec, functions);
            half_step = calc_next_vec(h / 2, t_current, x_current_vec, functions);
            res_with_step_div_two = calc_next_vec(h / 2, t_current + h / 2, half_step, functions);
            std::vector<double> discrepancy(x_current_vec.size());
            for(std::size_t i = 0; i < x_current_vec.size(); ++i) {
                discrepancy[i] = std::abs(res_with_step[i] - res_with_step_div_two[i]);
            }
            auto norm = *std::max_element(discrepancy.begin(), discrepancy.end());
            R = norm / (std::pow(2, p) - 1);
            if(R < eps / std::pow(2, p + 1)) {
                doubleStep = true;
            } else if(R > eps) {
                h /= 2;
                ++div_vec[div_vec.size() - 1];
            }
        } while(R > eps);
        return res_with_step;
    }

public:

    std::vector<double> get_t_result_vec() {
        return t_result_vec;
    }

    std::vector<std::vector<double>> get_x_result_vecs() {
        return x_result_vecs;
    }

    std::size_t get_step_divide_count() {
        return std::accumulate(div_vec.begin(), div_vec.end(), 0);
    }

    std::size_t get_step_doubling_count() {
        return std::accumulate(doubling_vec.begin(), doubling_vec.end(), 0);
    }

    std::size_t get_right_part_calc_count() {
        return right_part_calc_count;
    }

    std::vector<std::size_t> get_div_vec() {
        return div_vec;
    }

    std::vector<std::size_t> get_doubling_vec() {
        return doubling_vec;
    }

    std::vector<double> get_step_vec() {
        return step_vec;
    }

    void Execute(double h, double t_start, double t_finish, const std::vector<double>& x_start_vec,
               const std::vector<std::function<double(double, const std::vector<double>&)>>& functions, double eps, const bool stepCorrect = false){
        std::vector<double> x_current_vec = x_start_vec;
        double t_current = t_start;
        bool doubleStep = false;
        do {
            x_result_vecs.push_back(x_current_vec);
            t_result_vec.push_back(t_current);
            if(stepCorrect) {
                x_current_vec = richardson(h, t_current, x_current_vec, functions, eps, doubleStep);
                t_current += h;
            } else {
                x_current_vec = calc_next_vec(h, t_current, x_current_vec, functions);
                t_current += h;
            }
            step_vec.push_back(h);
        } while(t_current < t_finish);
    }

};


#endif // EILER_H
