#ifndef RADO2A_H
#define RADO2A_H
#include "Newton.h"

class Redo2A {

    private:

    std::vector<std::vector<double>> x_result_vecs;
    std::vector<double> t_result_vec;
    std::vector<double> step_vec;
    NewtonMethod nm;

    std::vector<std::vector<double>> kVec;

    std::vector<double> calculate_next_nu_vec(double h, double t_current, const std::vector<double>& x_current_vec, 
                        const std::vector<std::function<double(double, const std::vector<double>&)>>& F,
                        const std::vector<std::vector<std::function<double(double, const std::vector<double>&)>>>& J, double eps)
    {
        std::vector<double> cCoefs{1/3, 1};
        std::vector<std::vector<double>> aCoefs{{5/12, -1/12}, {3/4, 1/4}};

        std::vector<std::function<double(const std::vector<double>&)>> F1;
        std::vector<std::vector<std::function<double(const std::vector<double>&)>>> J1;

        for(std::size_t i = 0; i < F.size(); ++i) {
            for(std::size_t j = 0; j < cCoefs.size(); ++j) {
                F1.push_back([i, j, &F, &cCoefs, h, &x_current_vec, &aCoefs, &t_current](const std::vector<double>& nu){
                    std::vector<double> x_new;
                    for(std::size_t i1 = 0; i1 < F.size(); ++i1) {
                        double sum = 0;
                        for(std::size_t j1 = 0; j1 < cCoefs.size(); ++j1) {
                            sum += aCoefs[j][j1]*nu[i1 * cCoefs.size() + j1];
                        }
                        x_new.push_back(x_current_vec[i1] + h * sum);
                    }
                    return F[i](t_current + cCoefs[j] * h, x_new) - nu[i * cCoefs.size() + j];
                });

                J1.push_back({});
                for(std::size_t i1 = 0; i1 < F.size(); ++i1) {
                    for(std::size_t j1 = 0; j1 < cCoefs.size(); ++j1) {
                        J1[i * cCoefs.size() + j].push_back([i, j, i1, j1, &J, &cCoefs, h, &x_current_vec, &aCoefs, &t_current](const std::vector<double>& nu){
                            std::vector<double> x_new;
                            for(std::size_t i2 = 0; i2 < J.size(); ++i2) {
                                double sum = 0;
                                for(std::size_t j2 = 0; j2 < cCoefs.size(); ++j2) {
                                    sum += aCoefs[j1][j2]*nu[i2 * cCoefs.size() + j2];
                                }
                                x_new.push_back(x_current_vec[i2] + h * sum);
                            }
                            return (J[i][i1](t_current + cCoefs[j1] * h, x_new) - (i1 == i && j1 == j ? 1 : 0)) * 
                                            (x_current_vec[i1] + h * aCoefs[j][j1] * nu[i1 * cCoefs.size() + j1]);
                        });
                    }
                }
            }
        }

        return nm.newton(x_current_vec, F1, J1, eps);
    }




    std::vector<double> calc_next_vec(double h, double t_current, const std::vector<double>& x_current_vec,
                                      const std::vector<std::function<double(double, const std::vector<double>&)>>& F,
                                       const std::vector<std::vector<std::function<double(double, const std::vector<double>&)>>>& J,
                                      double eps){

        std::vector<double> nu = calculate_next_nu_vec(h, t_current, x_current_vec, F, J, eps);



        return nm.newton(x_current_vec, Fnew, Jnew, eps);
    }

};

#endif // RADO2A_H
