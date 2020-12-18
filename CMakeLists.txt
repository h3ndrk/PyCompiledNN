cmake_minimum_required(VERSION 3.5)
project(PyCompiledNN)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(Python3 COMPONENTS Interpreter Development NumPy)
find_package(Boost COMPONENTS python numpy REQUIRED)

# include(ExternalProject)
# ExternalProject_Add(CompiledNN
#     GIT_REPOSITORY https://github.com/bhuman/CompiledNN.git
#     GIT_TAG 9bcbbbb8c64c7c1234e252b294813b6b96b12e6d
#     CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}/CompiledNN
# )

add_subdirectory(CompiledNN)

Python3_add_library(PyCompiledNN main.cpp)
# target_include_directories(PyCompiledNN PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/CompiledNN/include)
# target_link_directories(PyCompiledNN PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/CompiledNN/lib)
target_include_directories(PyCompiledNN PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/CompiledNN/Src/CompiledNN/
    ${CMAKE_CURRENT_SOURCE_DIR}/CompiledNN/3rdParty/B-Human/
)
target_link_libraries(PyCompiledNN PRIVATE Boost::python Boost::numpy CompiledNN)
# target_compile_options()
# target_link_libraries(PyCompiledNN PRIVATE CompiledNN)
