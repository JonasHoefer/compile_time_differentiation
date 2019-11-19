#ifndef SYMBOLIC_DIFFERENTIATION_UTIL_HPP
#define SYMBOLIC_DIFFERENTIATION_UTIL_HPP

#include "ast.hpp"

template<auto a, auto b>
struct max
{
    static constexpr auto value = a < b ? b : a;
};

template<typename T>
struct var_count;

template<size_t i>
struct var_count<var<i>>
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

template<typename F>
using vars_t = std::array<double, var_count<F>::value>;

#endif //SYMBOLIC_DIFFERENTIATION_UTIL_HPP
