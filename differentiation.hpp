#ifndef SYMBOLIC_DIFFERENTIATION_DIFFERENTIATION_HPP
#define SYMBOLIC_DIFFERENTIATION_DIFFERENTIATION_HPP

#include "ast.hpp"

namespace diff
{
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

    template<size_t i, long c, size_t d>
    struct derivative<pow<var<i>, constant<c>>, d>
    {
        using type = std::conditional_t<i == d,
                times<constant<c>, pow<var<i>, constant<c - 1>>>,
                constant<0>>;
    };
}

#endif //SYMBOLIC_DIFFERENTIATION_DIFFERENTIATION_HPP
