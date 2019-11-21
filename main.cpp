#include <iostream>

#include "differentiation.hpp"
#include "util.hpp"
#include "literals.hpp"


using namespace diff;
using namespace diff::literals;

int main()
{
    auto f = e ^x;
    std::cout << f({x = 2, y = 4}) << std::endl;
    std::cout << D(f)({x = 2, y = 4}) << std::endl;
    std::cout << D(D(f))({x = 2, y = 4}) << std::endl;

    return 0;
}
