#ifndef EILERIMPLICITANYDIM_H
#define EILERIMPLICITANYDIM_H
#include "Newton.h"
#include "BaseMethod.h"

class EilerImplicitAnyDim : public BaseMethod {

private:

    NewtonMethod nm;


    std::vector<double> calc_next_vec(double h, double t_current, const std::vector<double>& x_current_vec,
                                      const std::vector<std::function<double(double, const std::vector<double>&)>>& F,
                                       const std::vector<std::vector<std::function<double(double, const std::vector<double>&)>>>& J,
                                      double eps){

        std::vector<std::function<double(const std::vector<double>&)>> Fnew;
    
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

    auto richardson(double& h, double t_current, const std::vector<double>& x_current_vec,
                    const std::vector<std::function<double(double, const std::vector<double>&)>>& F,
                    const std::vector<std::vector<std::function<double(double, const std::vector<double>&)>>>& J, 
                    double eps, bool& doubleStep) {
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
            res_with_step = calc_next_vec(h, t_current, x_current_vec, F, J, eps);
            half_step = calc_next_vec(h / 2, t_current, x_current_vec, F, J, eps);
            res_with_step_div_two = calc_next_vec(h / 2, t_current + h / 2, half_step, F, J, eps);
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

    EilerImplicitAnyDim() {
        p = 1;
    }

    uint32_t getNumOfSteps() {
        return nm.getNumOfSteps();
    }

    void Execute(double h, double t_start, double t_finish, const std::vector<double>& x_start_vec,
                 const std::vector<std::function<double(double, const std::vector<double>&)>>& F,
                  const std::vector<std::vector<std::function<double(double, const std::vector<double>&)>>>& J, double eps, const bool stepCorrect = false){

        std::vector<double> x_current_vec = x_start_vec;
        double t_current = t_start;
        bool doubleStep = false;
        do {
            x_result_vecs.push_back(x_current_vec);
            t_result_vec.push_back(t_current);
            if(stepCorrect) {
                x_current_vec = richardson(h, t_current, x_current_vec, F, J, eps, doubleStep);
                t_current += h;   
            } else {
                auto res_step = calc_next_vec(h, t_current, x_current_vec, F, J, eps);
                auto half_step = calc_next_vec(h / 2, t_current, x_current_vec, F, J, eps);
                auto res_with_step_div_two = calc_next_vec(h / 2, t_current + h / 2, half_step, F, J, eps);
                m_localError.push_back(localError(res_step, res_with_step_div_two));
                x_current_vec = res_step;
                t_current += h;
            }
            step_vec.push_back(h);
        } while(t_current < t_finish);
    }

};

#endif // EILERIMPLICITANYDIM_H
