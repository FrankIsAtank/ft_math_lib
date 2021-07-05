# CMake version expected
cmake_minimum_required(VERSION 3.18)

# Project title
project(FT_MATH_LIB)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# specify source file directories
set(DIR_SRC "${FT_MATH_LIB_SOURCE_DIR}/src")
set(DIR_MATRIX "${DIR_SRC}/matrix")
set(DIR_QUATERNION "${DIR_SRC}/quaternion")
set(DIR_VECTOR "${DIR_SRC}/vector")

# source files

file (GLOB CPP_FULL "")
file (GLOB HPP_FULL "")

# source : main
# set(SRC_MAIN "${DIR_SRC}/main.cpp")
# source_group("source" FILES ${SRC_MAIN})
# file (GLOB CPP_FULL ${SRC_MAIN})
# file (GLOB HPP_FULL "")

# source : matrix
file(GLOB_RECURSE SRC_MATRIX_CPP ${DIR_MATRIX}/*.cpp)
file(GLOB_RECURSE SRC_MATRIX_HPP ${DIR_MATRIX}/*.h ${DIR_MATRIX}/*.hpp)
source_group("source\\matrix" FILES ${SRC_MATRIX_CPP})
source_group("header\\matrix" FILES ${SRC_MATRIX_HPP})
list (APPEND CPP_FULL ${SRC_MATRIX_CPP})
list (APPEND HPP_FULL ${SRC_MATRIX_HPP})

# source : quaternion
file(GLOB_RECURSE SRC_QUATERNION_CPP ${DIR_QUATERNION}/*.cpp)
file(GLOB_RECURSE SRC_QUATERNION_HPP ${DIR_QUATERNION}/*.h ${DIR_QUATERNION}/*.hpp)
source_group("source\\quaternion" FILES ${SRC_QUATERNION_CPP})
source_group("header\\quaternion" FILES ${SRC_QUATERNION_HPP})
list (APPEND CPP_FULL ${SRC_QUATERNION_CPP})
list (APPEND HPP_FULL ${SRC_QUATERNION_HPP})

# source : vector
file(GLOB_RECURSE SRC_VECTOR_CPP ${DIR_VECTOR}/*.cpp)
file(GLOB_RECURSE SRC_VECTOR_HPP ${DIR_VECTOR}/*.h ${DIR_VECTOR}/*.hpp)
source_group("source\\vector" FILES ${SRC_VECTOR_CPP})
source_group("header\\vector" FILES ${SRC_VECTOR_HPP})
list (APPEND CPP_FULL ${SRC_VECTOR_CPP})
list (APPEND HPP_FULL ${SRC_VECTOR_HPP})

# include the files
add_library(FT_MATH_LIB ${CPP_FULL} ${HPP_FULL})
set_target_properties(FT_MATH_LIB PROPERTIES OUTPUT_NAME ft_math_lib)

# include other ft libraries
set(FT_LIB_ROOT $ENV{FT_ROOT})

# include ft_base_lib
include_directories(${FT_LIB_ROOT}/ft_base_lib/src)
include_directories(${FT_LIB_ROOT}/ft_platform_lib/src)

# define default include path
target_include_directories(FT_MATH_LIB PRIVATE "${DIR_SRC}")

