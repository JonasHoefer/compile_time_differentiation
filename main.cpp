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
    using f = plus<diff::pow<x, constant<3>>, diff::pow<x, constant<2>>>;
    using f_x = d<f, x>;

    f func;
    f_x func_x;

    std::map<size_t, double> vars = {{var_num<diff::x>::value, 2.0},
                                     {var_num<diff::y>::value, 4.0}};
    std::cout << "f(" << vars << ") = " << func(vars) << std::endl;
    std::cout << "f'(" << vars << ") = " << func_x(vars) << std::endl;


    auto test = (2_c ^ 3_c) * 17_c + 420_c;
    std::cout << test(vars) << std::endl;

    return 0;
}
