# Compile Time Differentiation

A small C++ library for calculating derivatives at compile time. 

```cpp
#include <iostream>

#include "differentiation.hpp"
#include "util.hpp"
#include "literals.hpp"


using namespace diff;
using namespace diff::literals;

int main()
{
    auto f = sin(x) + 2_c * (y ^ 3_c) * (x ^ 2_c);  // create a function
    auto df = D(f);  // differentiate it

    ast::vars_t vars = {x = 2, y = 4};

    std::cout << df(vars) << std::endl;  // evaluate it
}
```
