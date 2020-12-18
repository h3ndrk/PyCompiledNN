cmake_minimum_required(VERSION 3.5)
project(PyCompiledNN)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(Python3 COMPONENTS Interpreter Development NumPy)
find_package(Boost COMPONENTS python numpy REQUIRED)

add_subdirectory(CompiledNN)

Python3_add_library(PyCompiledNN main.cpp)
target_include_directories(PyCompiledNN PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/CompiledNN/Src/CompiledNN/
    ${CMAKE_CURRENT_SOURCE_DIR}/CompiledNN/3rdParty/B-Human/
)
target_link_libraries(PyCompiledNN PRIVATE Boost::python Boost::numpy CompiledNN)
