cmake_minimum_required(VERSION 3.14)
project(symbolic_differentiation)

set(CMAKE_CXX_STANDARD 17)

add_executable(symbolic_differentiation main.cpp differentiation.hpp ast.hpp util.hpp literals.hpp)