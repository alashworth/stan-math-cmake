cmake_minimum_required(VERSION 3.15)

project(StanMath
		VERSION 2.20
		DESCRIPTION "State-of-the-art package for statistical inference."
		HOMEPAGE_URL "https://github.com/stan-dev/math")

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

if (EXISTS ${PROJECT_BINARY_DIR}/conan_paths.cmake)
	include(${PROJECT_BINARY_DIR}/conan_paths.cmake)
endif ()

set(CMAKE_FIND_PACKAGE_SORT_ORDER NATURAL)
option(STAN_BUILD_TESTS "Build unit tests." ON)

find_package(Boost 1.72 REQUIRED OPTIONAL_COMPONENTS serialization mpi CONFIG)
find_package(Sundials 4.1 REQUIRED)
find_package(OpenCL 1.2 QUIET)
find_package(OpenCLPP QUIET)
find_package(Eigen3 3.3.3 REQUIRED)
find_package(TBB 2019 REQUIRED)
find_package(Threads REQUIRED)

set(STAN_OPENCL_DEVICE_ID "0" CACHE STRING "Desired device to run OpenCL-accelerated functions on.")
set(STAN_OPENCL_PLATFORM_ID "0" CACHE STRING "Desired OpenCL platform to run OpenCL-accelerated functions on.")

include(CheckCXXCompilerFlag)
include(CheckPIESupported)

check_pie_supported()
if(CMAKE_CXX_LINK_PIE_SUPPORTED)
	set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)
endif()

add_subdirectory(stan/math)

if (STAN_BUILD_TESTS)
	find_package(GTest 1.8 REQUIRED)
	add_subdirectory(test/unit)
endif ()