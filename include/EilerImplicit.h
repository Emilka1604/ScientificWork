#ifndef EILERIMPLICIT_H
#define EILERIMPLICIT_H

#include <vector>
#include <functional>
#include <math.h>
#include <algorithm>
#include <numeric>

class EilerImplicit {
    std::vector<double> x_result_vecs;
    std::vector<double> t_result_vec;
    std::size_t right_part_calc_count{0};
    std::vector<double> step_vec;

public:

    std::vector<double> get_t_result_vec() {
        return t_result_vec;
    }

    std::vector<double> get_x_result_vecs() {
        return x_result_vecs;
    }

    std::size_t get_right_part_calc_count() {
        return right_part_calc_count;
    }

    std::vector<double> get_step_vec() {
        return step_vec;
    }

    void Execute(double h, double t_start, double t_finish, double x_start,
               const std::function<double(double, double, double)>& f){
        double x_current = x_start;
        double t_current = t_start;
        do {
            x_result_vecs.push_back(x_current);
            t_result_vec.push_back(t_current);
            x_current = f(h, t_current, x_current);
            t_current += h;
            step_vec.push_back(h);
        } while(t_current < t_finish);
    }
};

#endif // EILERIMPLICIT_H
