cmake_minimum_required(VERSION 3.14)
project(symbolic_differentiation)

set(CMAKE_CXX_STANDARD 17)

add_executable(symbolic_differentiation src/main.cpp include/diff/differentiation.hpp include/diff/ast.hpp include/diff/util.hpp include/diff/literals.hpp)