#include <iostream>

#include "differentiation.hpp"
#include "util.hpp"

/**
 * print arrays
 */
template<typename T, size_t l>
std::ostream& operator<<(std::ostream& os, std::array<T, l> a)
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
    using f_t = plus<pow_x<0, 3>, pow_x<0, 2>>;
    using df_t = D<f_t, 1>;

    f_t f;
    df_t Df;

    vars_t<f_t> vars = {2};
    std::cout << "f(" << vars << ") = " << f(vars) << std::endl;
    std::cout << "f'(" << vars << ") = " << Df(vars) << std::endl;

    return 0;
}
