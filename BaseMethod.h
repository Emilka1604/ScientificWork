#ifndef BASEMETHOD_H
#define BASEMETHOD_H
#include <functional>
#include <vector>
#include <math.h>
#include <algorithm>
 #include <numeric>
#include <iostream>

class BaseMethod {
public:
    virtual void Execute(double h, double t_start, double t_finish, const std::vector<double>& x_start_vec,
               const std::vector<std::function<double(double, const std::vector<double>&)>>& functions, double eps) = 0;


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

protected:

    virtual std::vector<double> calc_next_vec(double h, double t_current, const std::vector<double>& x_current_vec,
                                      const std::vector<std::function<double(double, const std::vector<double>&)>>& functions) = 0;

    auto richardson(double& h, double t_current, const std::vector<double>& x_current_vec,
                    const std::vector<std::function<double(double, const std::vector<double>&)>>& functions, double eps) {
        double R = 0;
        std::vector<double> res_with_step;
        std::vector<double> half_step;
        std::vector<double> res_with_step_div_two;
        bool isFirstIter = true;
        div_vec.push_back(0);
        doubling_vec.push_back(0);
        do {
            if (isFirstIter) {
                res_with_step = calc_next_vec(h, t_current, x_current_vec, functions);
                isFirstIter = false;
            } else {
                res_with_step = std::move(half_step);               
            }
            half_step = calc_next_vec(h / 2, t_current, x_current_vec, functions);
            res_with_step_div_two = calc_next_vec(h / 2, t_current + h / 2, half_step, functions);
            std::vector<double> discrepancy(x_current_vec.size());
            for(std::size_t i = 0; i < x_current_vec.size(); ++i) {
                discrepancy[i] = std::abs(res_with_step[i] - res_with_step_div_two[i]);
            }
            auto norm = *std::max_element(discrepancy.begin(), discrepancy.end());
            R = norm / (std::pow(2, p) - 1);
            if(R < eps / std::pow(2, p + 1)) {
                h *= 2;
                ++doubling_vec[doubling_vec.size() - 1];
            } else if(R > eps) {
                h /= 2;
                ++div_vec[div_vec.size() - 1];
            }
        } while(R > eps);
        return res_with_step;
    }


    std::vector<std::vector<double>> x_result_vecs;
    std::vector<double> t_result_vec;
    std::vector<std::size_t> div_vec;
    std::vector<std::size_t> doubling_vec;
    std::size_t right_part_calc_count{0};
    std::size_t p;

};

#endif // BASEMETHOD_H
