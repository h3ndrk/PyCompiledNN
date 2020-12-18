cmake_minimum_required(VERSION 3.5)
project(CompiledNN)

find_package(Python3 COMPONENTS Interpreter Development NumPy)
find_package(Boost COMPONENTS python numpy REQUIRED)

Python3_add_library(CompiledNN main.cpp)
target_link_libraries(CompiledNN PRIVATE Boost::python Boost::numpy)
