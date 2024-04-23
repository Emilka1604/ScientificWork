#ifndef NEWTON_H
#define NEWTON_H
#include <vector>
#include <functional>
#include <cmath>
#include <iostream>

class NewtonMethod {

    uint32_t numOfSteps{};

public:

    std::vector<double> newton2on2(const std::vector<double>& startPoint, std::function<double(double, double)> f1,
                                   std::function<double(double, double)> f2,
                                   std::function<double(double, double)> df1dx,
                                   std::function<double(double, double)> df1dy,
                                   std::function<double(double, double)> df2dx,
                                   std::function<double(double, double)> df2dy,
                                   double eps) {
        double x = startPoint[0];
        double y = startPoint[1];

        while (true) {
            ++numOfSteps;

            double detJ = df1dx(x, y) * df2dy(x, y) - df2dx(x, y) * df1dy(x, y);
            double deltaX = (f1(x, y) * df2dy(x, y) - f2(x, y) * df1dy(x, y)) / detJ;
            double deltaY = (df1dx(x, y) * f2(x, y) - df2dx(x, y) * f1(x, y)) / detJ;

            x -= deltaX;
            y -= deltaY;

            if (std::abs(deltaX) < eps && std::abs(deltaY) < eps) {
                break;
            }
        }
        return std::vector<double>{x, y};
    }

    std::vector<double> newton3on3(const std::vector<double>& startPoint, std::function<double(double, double, double)> f1,
                                  std::function<double(double, double, double)> f2,
                                   std::function<double(double, double, double)> f3,
                                   std::function<double(double, double, double)> df1dx,
                                   std::function<double(double, double, double)> df1dy,
                                   std::function<double(double, double, double)> df1dz,
                                   std::function<double(double, double, double)> df2dx,
                                  std::function<double(double, double, double)> df2dy,
                                  std::function<double(double, double, double)> df2dz,
                                  std::function<double(double, double, double)> df3dx,
                                 std::function<double(double, double, double)> df3dy,
                                 std::function<double(double, double, double)> df3dz,
                                   double eps) {
        double x = startPoint[0];
        double y = startPoint[1];
        double z = startPoint[2];

        while (true) {

            ++numOfSteps;

            double detJ = df1dx(x, y, z) * (df2dy(x, y, z) * df3dz(x, y, z) - df3dy(x, y, z) * df2dz(x, y, z))
                        - df2dx(x, y, z) * (df1dy(x, y, z) * df3dz(x, y, z) - df3dy(x, y, z) * df1dz(x, y, z))
                        + df3dx(x, y, z) * (df1dy(x, y, z) * df2dz(x, y, z) - df2dy(x, y, z) * df1dz(x, y, z));

            double deltaX = (f1(x, y, z) * (df2dy(x, y, z) * df3dz(x, y, z) - df3dy(x, y, z) * df2dz(x, y, z))
                           - f2(x, y, z) * (df1dy(x, y, z) * df3dz(x, y, z) - df3dy(x, y, z) * df1dz(x, y, z))
                           + f3(x, y, z) * (df1dy(x, y, z) * df2dz(x, y, z) - df2dy(x, y, z) * df1dz(x, y, z))) / detJ;

            double deltaY = (df1dx(x, y, z) * (f2(x, y, z) * df3dz(x, y, z) - f3(x, y, z) * df2dz(x, y, z))
                           - df2dx(x, y, z) * (f1(x, y, z) * df3dz(x, y, z) - f3(x, y, z) * df1dz(x, y, z))
                           + df3dx(x, y, z) * (f1(x, y, z) * df2dz(x, y, z) - f2(x, y, z) * df1dz(x, y, z))) / detJ;

            double deltaZ = (df1dx(x, y, z) * (df2dy(x, y, z) * f3(x, y, z) - df3dy(x, y, z) * f2(x, y, z))
                           - df2dx(x, y, z) * (df1dy(x, y, z) * f3(x, y, z) - df3dy(x, y, z) * f1(x, y, z))
                           + df3dx(x, y, z) * (df1dy(x, y, z) * f2(x, y, z) - df2dy(x, y, z) * f1(x, y, z))) / detJ;

            x -= deltaX;
            y -= deltaY;
            z -= deltaZ;

            if (std::abs(deltaX) < eps && std::abs(deltaY) < eps && std::abs(deltaZ) < eps) {
                break;
            }
        }
        return std::vector<double>{x, y, z};
    }

    std::vector<double> solveUsingCramer(const std::vector<std::vector<double>>& A, const std::vector<double>& b) {
        int n = A.size();
        std::vector<double> x(n);

        double detA = det(A);

        if (detA == 0) {
            std::cout << "Determinant of the matrix A is zero, Cramer's method cannot be applied." << std::endl;
            return x;
        }

        for (int i = 0; i < n; i++) {
            std::vector<std::vector<double>> Ai = A;
            for (int j = 0; j < n; j++) {
                Ai[j][i] = b[j];
            }

            double detAi = det(Ai);

            x[i] = detAi / detA;
        }

        return x;
    }

    double det(std::vector<std::vector<double>> a) {
        const double EPS = 1E-9;
        double det = 1;
        for (std::size_t i=0; i<a.size(); ++i) {
            int k = i;
            for (std::size_t j=i+1; j<a.size(); ++j)
                if (std::abs (a[j][i]) > std::abs (a[k][i]))
                    k = j;
            if (std::abs (a[k][i]) < EPS) {
                det = 0;
                break;
            }
            swap (a[i], a[k]);
            if (i != k)
                det = -det;
            det *= a[i][i];
            for (std::size_t j=i+1; j<a.size(); ++j)
                a[i][j] /= a[i][i];
            for (std::size_t j=0; j<a.size(); ++j)
                if (j != i && std::abs (a[j][i]) > EPS)
                    for (std::size_t k=i+1; k<a.size(); ++k)
                        a[j][k] -= a[i][k] * a[j][i];
        }

        return det;
    }

    std::vector<double> newton(const std::vector<double>& startPoint,
                               const std::vector<std::function<double(const std::vector<double>&)>>& F,
                               const std::vector<std::vector<std::function<double(const std::vector<double>&)>>>& J, double eps)
    {
        auto currPoint = startPoint;
        bool needToStop = true;
        auto nextPoint = currPoint;
        do {
            ++numOfSteps;
            needToStop = true;
            nextPoint = newtonIteration(currPoint, F, J);
            for(std::size_t i = 0; i < currPoint.size(); ++i) {
                if(std::abs(nextPoint[i] - currPoint[i]) > eps) {
                    needToStop = false;
                    break;
                }
            }
            currPoint = nextPoint;
        } while(!needToStop);
        return nextPoint;
    }

    std::vector<double> newtonIteration(const std::vector<double>& currPoint,
                                        const std::vector<std::function<double(const std::vector<double>&)>>& F,
                                        const std::vector<std::vector<std::function<double(const std::vector<double>&)>>>& J) {
        std::vector<double> b;
        for(std::size_t i = 0; i < F.size(); ++i) {
            b.push_back(-F[i](currPoint));
        }

        std::vector<std::vector<double>> Jxk(J.size(), std::vector<double>(J[0].size()));
        for(std::size_t i = 0; i < J.size(); ++i) {
            for(std::size_t j = 0; j < J[0].size(); ++j) {
                Jxk[i][j] = J[i][j](currPoint);
            }
        }
        auto delta = solveUsingCramer(Jxk, b);
        std::vector<double> res;
        for(std::size_t i = 0; i < delta.size(); ++i) {
            res.push_back(currPoint[i] + delta[i]);
        }
        return res;
    }

    uint32_t getNumOfSteps() {
        return numOfSteps;
    }
};

#endif // NEWTON_H
