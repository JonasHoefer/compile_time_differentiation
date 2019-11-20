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
    
    using x = var<0>;

    using y = var<1>;

    using z = var<2>;

    template<typename T>
    struct var_num;

    template<size_t i>
    struct var_num<diff::var<i>>
    {
        static constexpr size_t value = i;
    };

    template<typename F, typename V>
    using d = D<F, var_num<V>::value>;
}

#endif //SYMBOLIC_DIFFERENTIATION_UTIL_HPP
