#ifndef SYMBOLIC_DIFFERENTIATION_UTIL_HPP
#define SYMBOLIC_DIFFERENTIATION_UTIL_HPP

#include "ast.hpp"

namespace diff
{
    template<auto a, auto b>
    struct max
    {
        static constexpr auto value = a < b ? b : a;
    };

    constexpr auto e = ast::e();

    constexpr auto x = ast::var<0>();

    constexpr auto y = ast::var<1>();

    constexpr auto z = ast::var<2>();

    template<typename T>
    struct var_num;

    template<size_t i>
    struct var_num<diff::ast::var<i>>
    {
        static constexpr size_t value = i;
    };

    template<typename F, typename V = typeof(x)>
    using d = derivative_t<F, var_num<std::remove_const_t<V>>::value>;

    template<typename T, typename V = typeof(x)>
    constexpr auto D(T t, V v = x)
    {
        return d<T, V>();
    }

    std::ostream& operator<<(std::ostream& os, const ast::vars_t& m)
    {
        os << m.begin()->second;
        for (auto i = ++m.begin(); i != m.end(); ++i)
            os << ", " << i->second;
        return os;
    }
}

#endif //SYMBOLIC_DIFFERENTIATION_UTIL_HPP
