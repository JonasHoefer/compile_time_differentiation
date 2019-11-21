#include <iostream>

#include "differentiation.hpp"
#include "util.hpp"
#include "literals.hpp"


using namespace diff;
using namespace diff::literals;

int main()
{
    auto f = sin(x) + 2_c * (y ^ 3_c) * (x ^ 2_c);
    ast::vars_t vars = {x = 2, y = 4.0};

    std::cout << "f(" << vars << ") = " << f(vars) << std::endl;
    std::cout << "f_x(" << vars << ") = " << D(f, x)(vars) << std::endl;
    std::cout << "f_y(" << vars << ") = " << D(f, y)(vars) << std::endl;
    std::cout << "f_xy(" << vars << ") = " << D(D(f, x), y)(vars) << std::endl;
    std::cout << "f_yx(" << vars << ") = " << D(D(f, y), x)(vars) << std::endl;

    return 0;
}
