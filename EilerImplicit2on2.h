#ifndef EILERIMPLICIT2ON2_H
#define EILERIMPLICIT2ON2_H
#include "Newton.h"

class EilerImplicit2on2{

private:

    std::vector<std::vector<double>> x_result_vecs;
    std::vector<double> t_result_vec;
    std::vector<double> step_vec;
    NewtonMethod nm;

    std::vector<double> calc_next_vec(double h, double t_current, const std::vector<double>& x_current_vec,
                                      std::function<double(double, double, double)> f1,
                                      std::function<double(double, double, double)> f2,
                                      std::function<double(double, double, double)> df1dx,
                                      std::function<double(double, double, double)> df1dy,
                                      std::function<double(double, double, double)> df2dx,
                                      std::function<double(double, double, double)> df2dy, double eps){

        std::function<double(double, double)> f1sys = [h, t_current, &x_current_vec, &f1](double x, double y){
            return x_current_vec[0] + h/2*(f1(t_current, x_current_vec[0], x_current_vec[1]) + f1(t_current+h, x, y)) - x;
        };

        std::function<double(double, double)> f2sys = [h, t_current, &x_current_vec, &f2](double x, double y){
            return x_current_vec[1] + h/2*(f2(t_current, x_current_vec[0], x_current_vec[1]) + f2(t_current+h, x, y)) - y;
        };

        std::function<double(double, double)> df1dxsys = [h, t_current, &x_current_vec, &df1dx](double x, double y){
            return h/2*(df1dx(t_current, x_current_vec[0], x_current_vec[1]) + df1dx(t_current+h, x, y)) - 1;
        };

        std::function<double(double, double)> df1dysys = [h, t_current, &x_current_vec, &df1dy](double x, double y){
            return h/2*(df1dy(t_current, x_current_vec[0], x_current_vec[1]) + df1dy(t_current+h, x, y));
        };

        std::function<double(double, double)> df2dxsys = [h, t_current, &x_current_vec, &df2dx](double x, double y){
            return h/2*(df2dx(t_current, x_current_vec[0], x_current_vec[1]) + df2dx(t_current+h, x, y));
        };

        std::function<double(double, double)> df2dysys = [h, t_current, &x_current_vec, &df2dy](double x, double y){
            return h/2*(df2dy(t_current, x_current_vec[0], x_current_vec[1]) + df2dy(t_current+h, x, y)) - 1;
        };

        return nm.newton2on2(x_current_vec, f1sys, f2sys, df1dxsys, df1dysys, df2dxsys, df2dysys, eps);
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
                 std::function<double(double, double, double)> f1,
                                                    std::function<double(double, double, double)> f2,
                                                    std::function<double(double, double, double)> df1dx,
                                                    std::function<double(double, double, double)> df1dy,
                                                    std::function<double(double, double, double)> df2dx,
                                                    std::function<double(double, double, double)> df2dy){

        std::vector<double> x_current_vec = x_start_vec;
        double t_current = t_start;
        bool doubleStep = false;
        do {
            x_result_vecs.push_back(x_current_vec);
            t_result_vec.push_back(t_current);
            x_current_vec = calc_next_vec(h, t_current, x_current_vec, f1, f2, df1dx, df1dy, df2dx, df2dy, 0.001);
            t_current += h;
            step_vec.push_back(h);
        } while(t_current < t_finish);
    }

};


#endif // EILERIMPLICIT2ON2_H
