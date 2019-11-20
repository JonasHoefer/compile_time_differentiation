#include <iostream>

#include "differentiation.hpp"
#include "util.hpp"

using namespace diff;

/**
 * print arrays
 */
template<typename T, size_t l>
std::ostream &operator<<(std::ostream &os, std::array<T, l> a)
{
    for (size_t i = 0; i < l - 1; ++i)
        os << a[i] << ", ";
    return os << a[l - 1];
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

    std::array<double, 1> vars = {2};
    std::cout << "f(" << vars << ") = " << func(vars) << std::endl;
    std::cout << "f'(" << vars << ") = " << func_x(vars) << std::endl;

    return 0;
}
