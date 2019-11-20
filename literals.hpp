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
        return constant<str_to_num<cs...>::value>();
    }

    template<typename LHS, typename RHS>
    times <LHS, RHS> operator*(LHS, RHS) noexcept
    {
        return times<LHS, RHS>{};
    }

    template<typename LHS, typename RHS>
    plus <LHS, RHS> operator+(LHS, RHS) noexcept
    {
        return plus<LHS, RHS>{};
    }

    template<typename BASE, typename EXP>
    pow <BASE, EXP> operator^(BASE, EXP) noexcept
    {
        return pow<BASE, EXP>{};
    }

}

#endif //SYMBOLIC_DIFFERENTIATION_LITERALS_HPP
