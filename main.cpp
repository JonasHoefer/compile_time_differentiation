#include <iostream>
#include <math.h>
#include <array>
#include <type_traits>

/*
 * AST
 */

template<size_t i>
struct x
{
    template<size_t var_count>
    double operator()(std::array<double, var_count> vars)
    {
        return vars.at(i);
    }
};

template<typename lhs_t, typename rhs_t>
struct plus
{
    lhs_t lhs;

    rhs_t rhs;

    template<size_t var_count>
    double operator()(std::array<double, var_count> vars)
    {
        return lhs(vars) + rhs(vars);
    }
};

template<typename lhs_t, typename rhs_t>
struct times
{
    lhs_t lhs;

    rhs_t rhs;

    template<size_t var_count>
    double operator()(std::array<double, var_count> vars)
    {
        return lhs(vars) * rhs(vars);
    }
};

template<size_t i, size_t e>
struct pow_x
{

    template<size_t var_count>
    double operator()(std::array<double, var_count> vars)
    {
        return std::pow(vars.at(i), e);
    }
};

template<long val>
struct constant
{
    template<size_t var_count>
    double operator()(std::array<double, var_count> vars)
    {
        return val;
    }
};


/*
 * helper
 */

template<auto a, auto b>
struct max
{
    static constexpr auto value = a < b ? b : a;
};

template<typename T>
struct var_count;

template<size_t i>
struct var_count<x<i>>
{
    static constexpr auto value = i;
};

template<typename lhs, typename rhs>
struct var_count<plus<lhs, rhs>>
{
    static constexpr auto value = max<var_count<lhs>::value, var_count<rhs>::value>::value;
};

template<typename lhs, typename rhs>
struct var_count<times<lhs, rhs>>
{
    static constexpr auto value = max<var_count<lhs>::value, var_count<rhs>::value>::value;
};

template<size_t i, size_t e>
struct var_count<pow_x<i, e>>
{
    static constexpr auto value = 1;
};

template<long v>
struct var_count<constant<v>>
{
    static constexpr auto value = 0;
};


/*
 * Derivatives
 */

template<typename T, size_t x_i>
struct D;

template<typename T, size_t x_i>
using D_t = typename D<T, x_i>::type;

template<size_t i, size_t x_i>
struct D<x<i>, x_i>
{
    using type = std::conditional_t<x_i == i, constant<1>, x<i>>;
};

template<typename lhs, typename rhs, size_t x_i>
struct D<plus<lhs, rhs>, x_i>
{
    using type = plus<D_t<lhs, x_i>, D_t<rhs, x_i>>;
};

template<typename lhs, typename rhs, size_t x_i>
struct D<times<lhs, rhs>, x_i>
{
    using type = plus<times<D_t<lhs, x_i>, rhs>, times<lhs, D_t<rhs, x_i>>>;
};

template<size_t i, size_t e, size_t x_i>
struct D<pow_x<i, e>, x_i>
{
    using type = std::conditional_t<x_i == i, times<constant<e>, pow_x<i, e - 1>>, constant<0>>;
};


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
    using df_t = D_t<f_t, 1>;

    f_t f;
    df_t Df;

    std::array<double, var_count<f_t>::value> vars = {2};
    std::cout << "f(" << vars << ") = " << f(vars) << std::endl;
    std::cout << "f'(" << vars << ") = " << Df(vars) << std::endl;

    return 0;
}
