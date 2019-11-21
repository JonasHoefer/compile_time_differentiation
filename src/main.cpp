#include <iostream>
#include <diff/simplify.h>

#include "diff/differentiation.hpp"
#include "diff/util.hpp"
#include "diff/literals.hpp"


using namespace diff;
using namespace diff::literals;

int main()
{
    auto f = ln(e ^ (2_c * x));

    ast::vars_t var = {x = 100};
    std::cout << f << " = " << f(var) << std::endl;
    std::cout << D(f) << " = " << D(f)(var) << std::endl;
    std::cout << D(D(f))(var) << std::endl;

    return 0;
}
