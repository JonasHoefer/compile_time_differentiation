#include <iostream>

#include "differentiation.hpp"
#include "util.hpp"
#include "literals.hpp"


using namespace diff;
using namespace diff::literals;

int main()
{
    auto f = sin(x) + 2_c * (x ^ 3_c) + 3_c * (x ^ 2_c);
    ast::vars_t vars = {x = 2, y = 4.0};

    std::cout << "f(" << vars << ") = " << f(vars) << std::endl;
    std::cout << "Df(" << vars << ") = " << D(f)(vars) << std::endl;

    return 0;
}
