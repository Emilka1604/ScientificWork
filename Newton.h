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

    uint32_t getNumOfSteps() {
        return numOfSteps;
    }
};

#endif // NEWTON_H
