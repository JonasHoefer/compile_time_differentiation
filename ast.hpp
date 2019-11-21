#ifndef SYMBOLIC_DIFFERENTIATION_AST_HPP
#define SYMBOLIC_DIFFERENTIATION_AST_HPP

#include <cmath>
#include <map>
#include <type_traits>

namespace diff
{
    using vars_t = std::map<size_t, double>;

    template<size_t i>
    struct var
    {
        static constexpr size_t id = i;

        std::pair<size_t, double> operator=(double v) const noexcept
        {
            return {i, v};
        }

        inline double operator()(const vars_t& vars) const noexcept
        {
            return vars.at(i);
        }
    };

    template<typename lhs_t, typename rhs_t>
    struct plus
    {
        lhs_t lhs;

        rhs_t rhs;

        inline double operator()(const vars_t& vars) const noexcept
        {
            return lhs(vars) + rhs(vars);
        }
    };

    template<typename lhs_t, typename rhs_t>
    struct times
    {
        lhs_t lhs;

        rhs_t rhs;

        inline double operator()(const vars_t& vars) const noexcept
        {
            return lhs(vars) * rhs(vars);
        }
    };

    template<typename B, typename E>
    struct pow
    {
        B b;

        E e;

        inline double operator()(const vars_t& vars) const noexcept
        {
            return std::pow(b(vars), e(vars));
        }
    };

    template<long val>
    struct constant
    {
        inline double operator()(const vars_t&) const noexcept
        {
            return val;
        }
    };
}


#endif //SYMBOLIC_DIFFERENTIATION_AST_HPP
