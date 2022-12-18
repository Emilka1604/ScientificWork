#ifndef EILER_H
#define EILER_H

#include <vector>
#include <functional>

#include "BaseMethod.h"

class Eiler : public BaseMethod{

public:

    Eiler() {
        p = 1;
    };

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
        for(std::size_t i = 0; i < x_current_vec.size(); ++i) {
            x_next_vec[i] = x_current_vec[i] + h * functions[i](t_current, x_current_vec);
        }
        ++right_part_calc_count;
        return x_next_vec;
    }
};


#endif // EILER_H
