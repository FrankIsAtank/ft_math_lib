# CMake version expected
cmake_minimum_required(VERSION 3.18)

# Project title
project(FT_MATH_LIB)

# Project name
set(OUT_NAME "ft_math_lib")

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# specify source file directories
set(DIR_SRC "${FT_MATH_LIB_SOURCE_DIR}/src")

# source files
file (GLOB CPP_FULL "")
file (GLOB HPP_FULL "")

# add a subfolder of source files
# and assign those files to their own filter/group
# name : group name (both source file directory name, and filter name)
macro(ft_add_group group_name)

	file(GLOB_RECURSE SRC_NEW_CPP "${DIR_SRC}/${group_name}/*.cpp")
	file(GLOB_RECURSE SRC_NEW_HPP "${DIR_SRC}/${group_name}/*.h" "${DIR_SRC}/${group_name}/*.hpp")
	source_group("source\\${group_name}" FILES ${SRC_NEW_CPP})
	source_group("header\\${group_name}" FILES ${SRC_NEW_HPP})
	list (APPEND CPP_FULL ${SRC_NEW_CPP})
	list (APPEND HPP_FULL ${SRC_NEW_HPP})

endmacro()

ft_add_group("matrix")
ft_add_group("quaternion")
ft_add_group("vector")

# include the files
add_library(FT_MATH_LIB ${CPP_FULL} ${HPP_FULL})
set_target_properties(FT_MATH_LIB PROPERTIES OUTPUT_NAME ${OUT_NAME})


set(FT_LIB_ROOT $ENV{FT_ROOT})

# output files to common directory
set_target_properties(FT_MATH_LIB PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${FT_LIB_ROOT}/bin/Debug"
	ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${FT_LIB_ROOT}/bin/Release"
)

include_directories(${FT_LIB_ROOT}/ft_base_lib/src)
include_directories(${FT_LIB_ROOT}/ft_math_lib/src)
include_directories(${FT_LIB_ROOT}/ft_platform_lib/src)

