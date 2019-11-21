#include <iostream>

#include "../include/diff/differentiation.hpp"
#include "../include/diff/util.hpp"
#include "../include/diff/literals.hpp"


using namespace diff;
using namespace diff::literals;

int main()
{
    auto f = (e ^ (2_c * x));
    std::cout << f({x = 0.5}) << std::endl;
    std::cout << D(f)({x = 0.5}) << std::endl;
    std::cout << D(D(f))({x = 0.5}) << std::endl;

    return 0;
}
