#ifndef SYMBOLIC_DIFFERENTIATION_SIMPLIFY_HPP
#define SYMBOLIC_DIFFERENTIATION_SIMPLIFY_HPP

#include "ast.hpp"

namespace diff
{
    /**
     * Predicate on ASTs. True if the amount of nodes can be reduced by simplify_t
     *
     * @tparam T - an AST
     */
    template <typename T>
    struct simplifiable;

    template <typename T>
    inline constexpr bool simplifiable_v = simplifiable<T>::value;

    /*
     * base case
     */

    template <long c>
    struct simplifiable<ast::constant<c>>
    {
        static constexpr bool value = false;
    };

    template <>
    struct simplifiable<ast::e>
    {
        static constexpr bool value = false;
    };

    template <size_t i>
    struct simplifiable<ast::var<i>>
    {
        static constexpr bool value = false;
    };

    /*
     * plus
     */

    template <typename LHS, typename RHS>
    struct simplifiable<ast::plus<LHS, RHS>>
    {
        static constexpr bool value = simplifiable_v<LHS> || simplifiable_v<RHS>;
    };

    template <typename RHS>
    struct simplifiable<ast::plus<ast::constant<0>, RHS>>
    {
        static constexpr bool value = true;
    };

    template <typename LHS>
    struct simplifiable<ast::plus<LHS, ast::constant<0>>>
    {
        static constexpr bool value = true;
    };

    /*
     * minus
     */

    template <typename LHS, typename RHS>
    struct simplifiable<ast::minus<LHS, RHS>>
    {
        static constexpr bool value = simplifiable_v<LHS> || simplifiable_v<RHS>;
    };

    template <typename LHS>
    struct simplifiable<ast::minus<LHS, ast::constant<0>>>
    {
        static constexpr bool value = true;
    };

    /*
     * times
     */

    template <typename LHS, typename RHS>
    struct simplifiable<ast::times<LHS, RHS>>
    {
        static constexpr bool value = simplifiable_v<LHS> || simplifiable_v<RHS>;
    };

    template <typename RHS>
    struct simplifiable<ast::times<ast::constant<0>, RHS>>
    {
        static constexpr bool value = true;
    };

    template <typename RHS>
    struct simplifiable<ast::times<ast::constant<1>, RHS>>
    {
        static constexpr bool value = true;
    };

    template <typename LHS>
    struct simplifiable<ast::times<LHS, ast::constant<0>>>
    {
        static constexpr bool value = true;
    };

    template <typename LHS>
    struct simplifiable<ast::times<LHS, ast::constant<1>>>
    {
        static constexpr bool value = true;
    };

    /*
     * divide
     */

    template <typename LHS, typename RHS>
    struct simplifiable<ast::divide<LHS, RHS>>
    {
        static constexpr bool value = simplifiable_v<LHS> || simplifiable_v<RHS>;
    };

    template <typename RHS>
    struct simplifiable<ast::divide<ast::constant<0>, RHS>>
    {
        static constexpr bool value = true;
    };

    template <typename T>
    struct simplifiable<ast::divide<T, T>>
    {
        static constexpr bool value = true;
    };

    /*
     * pow
     */

    template <typename B, typename E>
    struct simplifiable<ast::pow<B, E>>
    {
        static constexpr bool value = simplifiable_v<B> || simplifiable_v<E>;
    };

    template <typename B>
    struct simplifiable<ast::pow<B, ast::constant<0>>>
    {
        static constexpr bool value = true;
    };


    /*
     * functions
     */

    template <typename T>
    struct simplifiable<ast::ln<T>>
    {
        static constexpr bool value = simplifiable_v<T>;
    };


    /**
     * Tries to reduce the amount of nodes in a given AST
     *
     * @tparam T - an AST
     */

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


    /**
     * Repeatedly applies simplify_t until simplifiable_v is false.
     *
     * @tparam T - an AST
     */

    template <typename T, typename = void>
    struct reduce;

    template <typename T>
    using reduce_t = typename reduce<T>::type;

    template <typename T>
    struct reduce<T, std::enable_if_t<simplifiable_v<T>, void>>
    {
        using type = reduce_t<simplify_t<T>>;
    };

    template <typename T>
    struct reduce<T, std::enable_if_t<!simplifiable_v<T>, void>>
    {
        using type = T;
    };
}

#endif //SYMBOLIC_DIFFERENTIATION_SIMPLIFY_HPP
