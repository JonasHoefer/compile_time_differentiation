#ifndef SYMBOLIC_DIFFERENTIATION_DIFFERENTIATION_HPP
#define SYMBOLIC_DIFFERENTIATION_DIFFERENTIATION_HPP

#include "ast.hpp"

template<typename T, size_t x_i>
struct derivative;

template<typename T, size_t x_i>
using D = typename derivative<T, x_i>::type;

template<size_t i, size_t x_i>
struct derivative<var<i>, x_i>
{
    using type = std::conditional_t<x_i == i, constant<1>, var<i>>;
};

template<typename lhs, typename rhs, size_t x_i>
struct derivative<plus<lhs, rhs>, x_i>
{
    using type = plus<D<lhs, x_i>, D<rhs, x_i>>;
};

template<typename lhs, typename rhs, size_t x_i>
struct derivative<times<lhs, rhs>, x_i>
{
    using type = plus<times<D<lhs, x_i>, rhs>, times<lhs, D<rhs, x_i>>>;
};

template<size_t i, size_t e, size_t x_i>
struct derivative<pow_var<i, e>, x_i>
{
    using type = std::conditional_t<x_i == i, times<constant<e>, pow_var<i, e - 1>>, constant<0>>;
};


#endif //SYMBOLIC_DIFFERENTIATION_DIFFERENTIATION_HPP
