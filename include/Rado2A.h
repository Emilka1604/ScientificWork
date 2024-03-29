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

    std::vector<double> calc_next_k_vec(double h, double t_current, const std::vector<double>& x_current_vec, 
                        const std::vector<std::function<double(double, const std::vector<double>&)>>& F,
                        const std::vector<std::vector<std::function<double(double, const std::vector<double>&)>>>& J)
    {
        std::vector<double> cCoefs{1/3, 1};
        std::vector<std::vector<double>> aCoefs{{5/12, -1/12}, {3/4, 1/4}};

        const std::vector<std::function<double(double, const std::vector<double>&)>> F1;
        const std::vector<std::vector<std::function<double(double, const std::vector<double>&)>>> J1;

        for(std::size_t i = 0; i < F.size(); ++i) {
            for(std::size_t j = 0; j < cCoefs.size(); ++j) {
                F1.push_back([i, j, &F, &cCoefs, h, &x_current_vec, &aCoefs](const std::vector<double>& nu){
                    std::vector<double> x_new;
                    for(std::size_t i1 = 0; i1 < F.size(); ++i1) {
                        double sum = 0;
                        for(std::size_t j1 = 0; j1 < cCoefs.size(); ++j1) {
                            sum += aCoefs[j][j1]*nu[]
                        }
                    }
                });
            }
        }



        // std::vector<std::vector<double>> res;
        // for(std::size_t i = 0; i < F.size(); ++i) {
        //     std::vector<std::function<double(const std::vector<double>&)>> Fnew;
        //     for(std::size_t j = 0; j < cCoefs.size(); ++j) {
        //         Fnew.push_back([h, t_current, &x_current_vec, &F, j, &cCoefs, &aCoefs](const std::vector<double>& nu){
        //             double sum = 0;
        //             for(std::size_t k = 0; k < cCoefs.size(); ++k) {
        //                 sum += nu[k] * aCoefs[j][k];
        //             }    
        //             return F[j](t_current + h * cCoefs[j], x_current_vec[j] + sum);
        //             // return 0;
        //         });
        //     }
        // }

    }




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

};

#endif // RADO2A_H
