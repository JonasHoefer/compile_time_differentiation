#ifndef SYMBOLIC_DIFFERENTIATION_AST_HPP
#define SYMBOLIC_DIFFERENTIATION_AST_HPP

#include <math.h>
#include <array>
#include <type_traits>

template<size_t i>
struct var
{
    template<size_t var_count>
    double operator()(std::array<double, var_count> vars)
    {
        return vars.at(i);
    }
};

using x = var<0>;

using y = var<1>;

using z = var<2>;


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


#endif //SYMBOLIC_DIFFERENTIATION_AST_HPP
