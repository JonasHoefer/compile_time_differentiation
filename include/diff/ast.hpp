#ifndef SYMBOLIC_DIFFERENTIATION_AST_HPP
#define SYMBOLIC_DIFFERENTIATION_AST_HPP

#include <cmath>
#include <map>
#include <type_traits>

namespace diff::ast
{
    using vars_t = std::map<size_t, double>;

    template<size_t i>
    struct var
    {
        static constexpr size_t id = i;

        std::pair<size_t, double> operator=(double v) const noexcept
        {
            return {id, v};
        }

        constexpr inline double operator()(const vars_t& vars) const noexcept
        {
            return vars.at(i);
        }
    };

    template<typename lhs_t, typename rhs_t>
    struct plus
    {
        static constexpr lhs_t lhs{};

        static constexpr rhs_t rhs{};

        constexpr inline double operator()(const vars_t& vars) const noexcept
        {
            return lhs(vars) + rhs(vars);
        }
    };

    template<typename lhs_t, typename rhs_t>
    struct minus
    {
        static constexpr lhs_t lhs{};

        static constexpr rhs_t rhs{};

        constexpr inline double operator()(const vars_t& vars) const noexcept
        {
            return lhs(vars) - rhs(vars);
        }
    };

    template<typename lhs_t, typename rhs_t>
    struct times
    {
        static constexpr lhs_t lhs{};

        static constexpr rhs_t rhs{};

        constexpr inline double operator()(const vars_t& vars) const noexcept
        {
            return lhs(vars) * rhs(vars);
        }
    };

    template<typename lhs_t, typename rhs_t>
    struct divide
    {
        static constexpr lhs_t lhs{};

        static constexpr rhs_t rhs{};

        constexpr inline double operator()(const vars_t& vars) const noexcept
        {
            return lhs(vars) / rhs(vars);
        }
    };

    template<typename B, typename E>
    struct pow
    {
        static constexpr B b{};

        static constexpr E e{};

        constexpr inline double operator()(const vars_t& vars) const noexcept
        {
            return std::pow(b(vars), e(vars));
        }
    };

    template<long val>
    struct constant
    {
        constexpr inline double operator()(const vars_t&) const noexcept
        {
            return val;
        }
    };

    template<typename T>
    struct sin
    {
        static constexpr T t{};

        constexpr inline double operator()(const vars_t& vars) const noexcept
        {
            return std::sin(t(vars));
        }
    };

    template<typename T>
    struct cos
    {
        static constexpr T t{};

        constexpr inline double operator()(const vars_t& vars) const noexcept
        {
            return std::cos(t(vars));
        }
    };

    template<typename T>
    struct ln
    {
        static constexpr T t{};

        constexpr inline double operator()(const vars_t& vars) const noexcept
        {
            return std::log(t(vars));
        }
    };

    struct e
    {
        constexpr inline double operator()(const vars_t&) const noexcept
        {
            return M_E;
        }
    };
}


#endif //SYMBOLIC_DIFFERENTIATION_AST_HPP
