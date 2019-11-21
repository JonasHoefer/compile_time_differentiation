#include <iostream>

#include "diff/differentiation.hpp"
#include "diff/literals.hpp"
#include "diff/util.hpp"
#include <diff/simplify.h>


using namespace diff;
using namespace diff::literals;

int main()
{
    auto f = ln(e ^ (2_c * x));

    auto g = 4_c + 0_c + (7_c + 0_c) + 0_c;
    auto gs = reduce_t<typeof(g)>();
    std::cout << g << " - " << gs << std::endl;

    ast::vars_t var = {x = 100};
    std::cout << f(var) << std::endl;
    std::cout << D(f)(var) << std::endl;
    std::cout << D(D(f))(var) << std::endl;

    return 0;
}
