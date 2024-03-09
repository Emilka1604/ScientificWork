#include "switcher.h"

#ifdef newtontest

#include "Newton.h"

int main() {

    NewtonMethod nm;
    auto res = nm.solveUsingCramer({{2,3,1},{3,-1,2},{1,4,-1}}, {1, 1, 2});
    for(const auto& el : res) {
        std::cout << el << " ";
    }

    return 0;
}

#endif
