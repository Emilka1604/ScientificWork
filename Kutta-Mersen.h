#ifndef KUTTAMERSEN_H
#define KUTTAMERSEN_H

#include "BaseMethod.h"

class KuttaMersen : public BaseMethod {
public:

    void Execute(double h, double t_start, double t_finish, const std::vector<double>& x_start_vec,
               const std::vector<std::function<double(double, const std::vector<double>&)>>& functions, double eps) override {
        std::vector<double> x_current_vec = x_start_vec;
        double t_current = t_start;
        do {
            x_result_vecs.push_back(x_current_vec);
            t_result_vec.push_back(t_current);
            x_current_vec = step_selection(h, t_current, x_current_vec, functions, eps);
            t_current += h;
        } while(t_current < t_finish);
    }

private:

    std::vector<double> step_selection(double& h, double t_current, const std::vector<double>& x_current_vec,
                    const std::vector<std::function<double(double, const std::vector<double>&)>>& functions, double eps) {
        double R = 0;
        std::vector<double> x_vec;
//        std::vector<double> x_vec_2;
        div_vec.push_back(0);
        doubling_vec.push_back(0);
        do {
            auto nu1 = this->nu1(h, t_current, x_current_vec, functions);
            auto nu2 = this->nu2(h, t_current, nu1, x_current_vec, functions);
            auto nu3 = this->nu3(h, t_current, nu1, nu2, x_current_vec, functions);
            auto nu4 = this->nu4(h, t_current, nu1, nu3, x_current_vec, functions);
            auto nu5 = this->nu5(h, t_current, nu1, nu3, nu4, x_current_vec, functions);
            right_part_calc_count += 5;
            x_vec = x_vec_calc(h, x_current_vec, nu1, nu4, nu5);
//            x_vec_2 = x_vec_2_calc(h, x_current_vec, nu1, nu3, nu4);
            R = this->R(nu1, nu3, nu4, nu5);
            if(R < eps / 30) {
                h *= 2;
                ++doubling_vec[doubling_vec.size() - 1];
            } else if(R > eps) {
                h /= 2;
                ++div_vec[div_vec.size() - 1];
            }
        } while(R > eps);
        return x_vec;
    }

    std::vector<double> calc_next_vec(double h, double t_current, const std::vector<double>& x_current_vec,
                                      const std::vector<std::function<double(double, const std::vector<double>&)>>& functions) override {

        return {};
    }

    std::vector<double> x_vec_calc(double h, const std::vector<double>& x_current_vec,
                                   std::vector<double> nu1, std::vector<double> nu4, std::vector<double> nu5) {
        std::vector<double> x_next_vec(x_current_vec.size());
        for(std::size_t i = 0; i < x_current_vec.size(); ++i) {
            x_next_vec[i] = x_current_vec[i] + (nu1[i] + 4 * nu4[i] + nu5[i]) / 6;
        }
        return x_next_vec;
    }

//    std::vector<double> x_vec_2_calc(double h, const std::vector<double>& x_current_vec,
//                                   std::vector<double> nu1, std::vector<double> nu3, std::vector<double> nu4) {
//        std::vector<double> x_next_vec(x_current_vec.size());
//        for(std::size_t i = 0; i < x_current_vec.size(); ++i) {
//            x_next_vec[i] = x_current_vec[i] + (nu1[i] - 3 * nu3[i] + 4 * nu4[i]) / 2;
//        }
//        return x_next_vec;
//    }

    double R(const std::vector<double>& nu1,const std::vector<double>& nu3,
             std::vector<double>& nu4, std::vector<double>& nu5) {
        std::vector<double> discrepancy(nu1.size());
        for(std::size_t i = 0; i < nu1.size(); ++i) {
            discrepancy[i] = std::abs(-2 * nu1[i] + 9 * nu3[i] - 8 * nu4[i] + nu5[i]);
        }
        return *std::max_element(discrepancy.begin(), discrepancy.end()) / 30;
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
            x_vec_new[i] = x_vec[i] + nu1[i] / 3;
        }
        std::vector<double> nu2(x_vec.size());
        for(std::size_t i = 0; i < x_vec.size(); ++i) {
            nu2[i] = h * functions[i](t + h / 3, x_vec_new);
        }
        return nu2;
    }

    std::vector<double> nu3(double h, double t, const std::vector<double>& nu1,const std::vector<double>& nu2,
            const std::vector<double>& x_vec, const std::vector<std::function<double(double, const std::vector<double>&)>>& functions) {

        std::vector<double> x_vec_new(x_vec.size());
        for(std::size_t i = 0; i < x_vec.size(); ++i) {
            x_vec_new[i] = x_vec[i] + nu1[i] / 6 + nu2[i] / 6;
        }
        std::vector<double> nu3(x_vec.size());
        for(std::size_t i = 0; i < x_vec.size(); ++i) {
            nu3[i] = h * functions[i](t + h / 3, x_vec_new);
        }
        return nu3;
    }

    std::vector<double> nu4(double h, double t, const std::vector<double>& nu1,const std::vector<double>& nu3,
            const std::vector<double>& x_vec, const std::vector<std::function<double(double, const std::vector<double>&)>>& functions) {

        std::vector<double> x_vec_new(x_vec.size());
        for(std::size_t i = 0; i < x_vec.size(); ++i) {
            x_vec_new[i] = x_vec[i] + nu1[i] / 8 + 3 * nu3[i] / 8;
        }
        std::vector<double> nu4(x_vec.size());
        for(std::size_t i = 0; i < x_vec.size(); ++i) {
            nu4[i] = h * functions[i](t + h / 2, x_vec_new);
        }
        return nu4;
    }

    std::vector<double> nu5(double h, double t, const std::vector<double>& nu1,const std::vector<double>& nu3,
        std::vector<double>& nu4, const std::vector<double>& x_vec,
                            const std::vector<std::function<double(double, const std::vector<double>&)>>& functions) {

        std::vector<double> x_vec_new(x_vec.size());
        for(std::size_t i = 0; i < x_vec.size(); ++i) {
            x_vec_new[i] = x_vec[i] + nu1[i] / 2 - 3 * nu3[i] / 2 + 2 * nu4[i];
        }
        std::vector<double> nu5(x_vec.size());
        for(std::size_t i = 0; i < x_vec.size(); ++i) {
            nu4[i] = h * functions[i](t + h, x_vec_new);
        }
        return nu4;
    }




};

#endif // KUTTAMERSEN_H
