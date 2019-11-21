#ifndef SYMBOLIC_DIFFERENTIATION_DIFFERENTIATION_HPP
#define SYMBOLIC_DIFFERENTIATION_DIFFERENTIATION_HPP

#include "ast.hpp"

namespace diff
{
    template<typename T, size_t x_i>
    struct derivative;

    template<typename T, size_t x_i>
    using derivative_t = typename derivative<T, x_i>::type;

    template<size_t i, size_t x_i>
    struct derivative<ast::var<i>, x_i>
    {
        using type = std::conditional_t<x_i == i, ast::constant<1>, ast::constant<0>>;
    };

    template<long c, size_t x_i>
    struct derivative<ast::constant<c>, x_i>
    {
        using type = ast::constant<0>;
    };

    template<typename lhs, typename rhs, size_t x_i>
    struct derivative<ast::plus<lhs, rhs>, x_i>
    {
        using type = ast::plus<derivative_t<lhs, x_i>, derivative_t<rhs, x_i>>;
    };

    template<typename lhs, typename rhs, size_t x_i>
    struct derivative<ast::times<lhs, rhs>, x_i>
    {
        using type = ast::plus<ast::times<derivative_t<lhs, x_i>, rhs>, ast::times<lhs, derivative_t<rhs, x_i>>>;
    };

    template<size_t i, long c, size_t d>
    struct derivative<ast::pow<ast::var<i>, ast::constant<c>>, d>
    {
        using type = std::conditional_t<i == d,
                ast::times<ast::constant<c>, ast::pow<ast::var<i>, ast::constant<c - 1>>>,
                ast::constant<0>>;
    };

    template<typename T, size_t x_i>
    struct derivative<ast::sin<T>, x_i>
    {
        using type = ast::times<derivative_t<T, x_i>, ast::cos<T>>;
    };

    template<typename T, size_t x_i>
    struct derivative<ast::cos<T>, x_i>
    {
        using type = ast::times<derivative_t<T, x_i>, ast::times<ast::constant<-1>, ast::sin<T>>>;
    };
}

#endif //SYMBOLIC_DIFFERENTIATION_DIFFERENTIATION_HPP
