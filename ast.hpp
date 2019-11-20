#ifndef SYMBOLIC_DIFFERENTIATION_AST_HPP
#define SYMBOLIC_DIFFERENTIATION_AST_HPP

#include <math.h>
#include <map>
#include <type_traits>

namespace diff
{
    template<size_t i>
    struct var
    {
        inline double operator()(std::map<size_t, double> vars) const noexcept
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

        inline double operator()(std::map<size_t, double> vars) const noexcept
        {
            return lhs(vars) + rhs(vars);
        }
    };

    template<typename lhs_t, typename rhs_t>
    struct times
    {
        lhs_t lhs;

        rhs_t rhs;

        inline double operator()(std::map<size_t, double> vars) const noexcept
        {
            return lhs(vars) * rhs(vars);
        }
    };

    template<typename B, typename E>
    struct pow
    {
        B b;

        E e;

        inline double operator()(std::map<size_t, double> vars) const noexcept
        {
            return std::pow(b(vars), e(vars));
        }
    };

    template<long val>
    struct constant
    {
        inline double operator()(std::map<size_t, double> vars) const noexcept
        {
            return val;
        }
    };
}


#endif //SYMBOLIC_DIFFERENTIATION_AST_HPP
