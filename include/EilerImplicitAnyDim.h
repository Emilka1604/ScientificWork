#ifndef EILERIMPLICITANYDIM_H
#define EILERIMPLICITANYDIM_H
#include "Newton.h"

class EilerImplicitAnyDim{

private:

    std::vector<std::vector<double>> x_result_vecs;
    std::vector<double> t_result_vec;
    std::vector<double> step_vec;
    NewtonMethod nm;


    std::vector<double> calc_next_vec(double h, double t_current, const std::vector<double>& x_current_vec,
                                      const std::vector<std::function<double(double, const std::vector<double>&)>>& F,
                                       const std::vector<std::vector<std::function<double(double, const std::vector<double>&)>>>& J,
                                      double eps){

        std::vector<std::function<double(const std::vector<double>&)>> Fnew;
        \
        for(std::size_t i = 0; i < F.size(); ++i) {
            Fnew.push_back([h, t_current, &x_current_vec, &F, i](const std::vector<double>& x) {
                return x_current_vec[i] + h/2*(F[i](t_current, x_current_vec) + F[i](t_current+h, x))-x[i];
            });
        }

        std::vector<std::vector<std::function<double(const std::vector<double>&)>>> Jnew;

        for(std::size_t i = 0; i < J.size(); ++i) {
            Jnew.push_back({});
            for(std::size_t j = 0; j < J[0].size(); ++j) {
                Jnew[i].push_back([h, t_current, &x_current_vec, &J, i, j](const std::vector<double>& x) {
                    return h/2*(J[i][j](t_current, x_current_vec) + J[i][j](t_current+h, x))-(i == j ? 1 : 0);
                });
            }
        }

        return nm.newton(x_current_vec, Fnew, Jnew, eps);
    }

public:

    uint32_t getNumOfSteps() {
        return nm.getNumOfSteps();
    }

    std::vector<double> get_t_result_vec() {
        return t_result_vec;
    }

    std::vector<std::vector<double>> get_x_result_vecs() {
        return x_result_vecs;
    }

    std::vector<double> get_step_vec() {
        return step_vec;
    }

    void Execute(double h, double t_start, double t_finish, const std::vector<double>& x_start_vec,
                 const std::vector<std::function<double(double, const std::vector<double>&)>>& F,
                  const std::vector<std::vector<std::function<double(double, const std::vector<double>&)>>>& J, double eps){

        std::vector<double> x_current_vec = x_start_vec;
        double t_current = t_start;
        bool doubleStep = false;
        do {
            std::cout << x_current_vec[0] << " " << x_current_vec[1] << "\n";
            x_result_vecs.push_back(x_current_vec);
            t_result_vec.push_back(t_current);
            x_current_vec = calc_next_vec(h, t_current, x_current_vec, F, J, eps);
            t_current += h;
            step_vec.push_back(h);
        } while(t_current < t_finish);
    }

};

#endif // EILERIMPLICITANYDIM_H
