#ifndef SYMBOLIC_DIFFERENTIATION_LITERALS_HPP
#define SYMBOLIC_DIFFERENTIATION_LITERALS_HPP

#include "ast.hpp"

namespace diff::literals
{
    constexpr long power(long b, unsigned long e) noexcept
    {
        return e == 0 ? 1 : b * power(b, e - 1);
    }

    template<char c, char... cs>
    struct str_to_num
    {
        static constexpr long value = (c - '0') * power(10, sizeof...(cs)) + str_to_num<cs...>::value;
    };

    template<char c>
    struct str_to_num<c>
    {
        static constexpr long value = c - '0';
    };

    template<char ... cs>
    auto operator ""_c()
    {
        return ast::constant<str_to_num<cs...>::value>();
    }

    template<typename LHS, typename RHS>
    ast::plus <LHS, RHS> operator+(LHS, RHS) noexcept
    { return {}; }

    template<typename LHS, typename RHS>
    ast::minus <LHS, RHS> operator-(LHS, RHS) noexcept
    { return {}; }

    template<typename LHS, typename RHS>
    ast::times <LHS, RHS> operator*(LHS, RHS) noexcept
    { return {}; }

    template<typename LHS, typename RHS>
    ast::divide <LHS, RHS> operator/(LHS, RHS) noexcept
    { return {}; }

    template<typename BASE, typename EXP>
    ast::pow <BASE, EXP> operator^(BASE, EXP) noexcept
    { return {}; }

    template<typename T>
    ast::sin <T> sin(T) noexcept
    { return {}; }

    template<typename T>
    ast::cos <T> cos(T) noexcept
    { return {}; }

    template<typename T>
    ast::ln <T> ln(T) noexcept
    { return {}; }
}

#endif //SYMBOLIC_DIFFERENTIATION_LITERALS_HPP
