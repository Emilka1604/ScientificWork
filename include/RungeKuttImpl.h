#ifndef RungeKuttImpl_H
#define RungeKuttImpl_H
#include "Newton.h"
#include "BaseMethod.h"

class RungeKuttImpl final : public BaseMethod {

    private:

    NewtonMethod nm;
    const std::vector<double> m_cCoefs;
    const std::vector<std::vector<double>> m_aCoefs;
    const std::vector<double> m_bCoefs;

    std::vector<std::vector<double>> kVec;

    std::vector<double> calculate_next(double h, double t_current, const std::vector<double>& x_current_vec, 
                        const std::vector<std::function<double(double, const std::vector<double>&)>>& F,
                        const std::vector<std::vector<std::function<double(double, const std::vector<double>&)>>>& J, double eps)
    {
        std::vector<std::function<double(const std::vector<double>&)>> F1;
        std::vector<std::vector<std::function<double(const std::vector<double>&)>>> J1;

        F1.reserve(F.size()*m_cCoefs.size());
        J1.reserve(F.size()*m_cCoefs.size());

        for(std::size_t i = 0; i < F.size(); ++i) {
            for(std::size_t j = 0; j < m_cCoefs.size(); ++j) {
                F1.push_back([this, i, j, &F, h, &x_current_vec, t_current](const std::vector<double>& nu){
                    std::vector<double> x_new;
                    for(std::size_t i1 = 0; i1 < F.size(); ++i1) {
                        double sum = 0;
                        for(std::size_t j1 = 0; j1 < m_cCoefs.size(); ++j1) {
                            sum += m_aCoefs[j][j1]*nu[i1 * m_cCoefs.size() + j1];
                        }
                        x_new.push_back(x_current_vec[i1] + h * sum);
                    }
                    return F[i](t_current + m_cCoefs[j] * h, x_new) - nu[i * m_cCoefs.size() + j];
                });

                J1.push_back({});
                J1[J1.size() - 1].reserve(F.size()*m_cCoefs.size());
                for(std::size_t i1 = 0; i1 < F.size(); ++i1) {
                    for(std::size_t j1 = 0; j1 < m_cCoefs.size(); ++j1) {
                        J1[i * m_cCoefs.size() + j].push_back([this, i, j, i1, j1, &J, h, &x_current_vec, t_current](const std::vector<double>& nu){
                            std::vector<double> x_new;
                            for(std::size_t i2 = 0; i2 < J.size(); ++i2) {
                                double sum = 0.0;
                                for(std::size_t j2 = 0; j2 < m_cCoefs.size(); ++j2) {
                                    sum += m_aCoefs[j][j2]*nu[i2 * m_cCoefs.size() + j2];
                                }
                                x_new.push_back(x_current_vec[i2] + h * sum);
                            }
                            return J[i][i1](t_current + m_cCoefs[j] * h, x_new) * h * m_aCoefs[j][j1] - (i1 == i && j1 == j ? 1.0 : 0.0);
                        });
                    }
                }
            }
        }

        std::vector<double> start(F.size()*m_cCoefs.size(), 0.5);

        std::vector<double> nu = nm.newton(start, F1, J1, eps);
        std::vector<double> res;
        res.reserve(F.size());

        for(std::size_t i = 0; i < F.size(); ++i) {
            double sum{};
            for(std::size_t j = 0; j < m_cCoefs.size(); ++j) {
                sum += m_bCoefs[j] * nu[i * m_cCoefs.size() + j];
            }
            res.push_back(x_current_vec[i] + h * sum);
        }

        return res;
    }

    public:

    RungeKuttImpl(const std::vector<double>& cCoefs, const std::vector<std::vector<double>>& aCoefs, 
            const std::vector<double>& bCoefs) : m_cCoefs{cCoefs}, m_aCoefs{aCoefs}, m_bCoefs{bCoefs} {
            p = 2 * m_cCoefs.size() - 1;
    }

    uint32_t getNumOfSteps() {
        return nm.getNumOfSteps();
    }

    void Execute(double h, double t_start, double t_finish, const std::vector<double>& x_start_vec,
                 const std::vector<std::function<double(double, const std::vector<double>&)>>& F,
                  const std::vector<std::vector<std::function<double(double, const std::vector<double>&)>>>& J, double eps){

        std::vector<double> x_current_vec = x_start_vec;
        double t_current = t_start;
        bool doubleStep = false;
        do {
            x_result_vecs.push_back(x_current_vec);
            t_result_vec.push_back(t_current);
            auto res_step = calculate_next(h, t_current, x_current_vec, F, J, eps);
            auto half_step = calculate_next(h / 2, t_current, x_current_vec, F, J, eps);
            auto res_with_step_div_two = calculate_next(h / 2, t_current + h / 2, half_step, F, J, eps);
            m_localError.push_back(localError(res_step, res_with_step_div_two));
            x_current_vec = std::move(res_step);
            t_current += h;
            step_vec.push_back(h);
        } while(t_current < t_finish);
    }

};

#endif // RungeKuttImpl_H
