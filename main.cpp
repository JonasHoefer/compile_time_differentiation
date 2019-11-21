#include <iostream>

#include "differentiation.hpp"
#include "util.hpp"
#include "literals.hpp"

using namespace diff;
using namespace diff::literals;

/**
 * print arrays
 */
std::ostream& operator<<(std::ostream& os, const std::map<size_t, double>& m)
{
    os << m.begin()->second;
    for (auto i = ++m.begin(); i != m.end(); ++i)
        os << ", " << i->second;
    return os;
}

/**
 * Main
 *
 * @return
 */
int main()
{
    auto f = 1_c + 2_c * (x ^ 3_c) + 3_c * (x ^ 2_c);
    vars_t vars = {x = 2, y = 4.0};

    std::cout << "f(" << vars << ") = " << f(vars) << std::endl;
    std::cout << "Df(" << vars << ") = " << D(f)(vars) << std::endl;

    return 0;
}
