#ifndef SYMBOLIC_DIFFERENTIATION_SIMPLIFY_H
#define SYMBOLIC_DIFFERENTIATION_SIMPLIFY_H

#include "ast.hpp"

namespace diff
{
    template<typename T>
    struct simplify;

    template<typename T>
    using simplify_t = typename simplify<T>::type;

    /*
     * base case
     */

    template<long c>
    struct simplify<ast::constant<c>>
    {
        using type = ast::constant<c>;
    };

    template<size_t i>
    struct simplify<ast::var<i>>
    {
        using type = ast::var<i>;
    };

    template<>
    struct simplify<ast::e>
    {
        using type = ast::e;
    };

    /*
     * plus
     */

    template<typename RHS>
    struct simplify<ast::plus<ast::constant<0>, RHS>>
    {
        using type = simplify_t<RHS>;
    };

    template<typename LHS>
    struct simplify<ast::plus<LHS, ast::constant<0>>>
    {
        using type = simplify_t<LHS>;
    };

    template<typename LHS, typename RHS>
    struct simplify<ast::plus<LHS, RHS>>
    {
        using type = ast::plus<simplify_t<LHS>, simplify_t<RHS>>;
    };

    /*
     * times
     */

    template<typename RHS>
    struct simplify<ast::times<ast::constant<1>, RHS>>
    {
        using type = simplify_t<RHS>;
    };

    template<typename LHS>
    struct simplify<ast::times<LHS, ast::constant<1>>>
    {
        using type = simplify_t<LHS>;
    };

    template<typename LHS, typename RHS>
    struct simplify<ast::times<LHS, RHS>>
    {
        using type = ast::times<simplify_t<LHS>, simplify_t<RHS>>;
    };

    template<typename RHS>
    struct simplify<ast::times<ast::constant<0>, RHS>>
    {
        using type = ast::constant<0>;
    };

    template<typename LHS>
    struct simplify<ast::times<LHS, ast::constant<0>>>
    {
        using type = ast::constant<0>;
    };

    /*
     * divide
     */

    template<typename LHS>
    struct simplify<ast::divide<LHS, ast::constant<1>>>
    {
        using type = simplify_t<LHS>;
    };

    template<typename T>
    struct simplify<ast::divide<T, T>>
    {
        using type = ast::constant<1>;
    };

    template<typename LHS, typename RHS>
    struct simplify<ast::divide<LHS, RHS>>
    {
        using type = ast::divide<simplify_t<LHS>, simplify_t<RHS>>;
    };

    /*
     * pow
     */

    template<typename B>
    struct simplify<ast::pow<B, ast::constant<0>>>
    {
        using type = ast::constant<1>;
    };

    template<typename B, typename E>
    struct simplify<ast::pow<B, E>>
    {
        using type = ast::pow<simplify_t<B>, simplify_t<E>>;
    };
}

#endif //SYMBOLIC_DIFFERENTIATION_SIMPLIFY_H
