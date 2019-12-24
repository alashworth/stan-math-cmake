find_path(cl_include_dir cl2.hpp PATH_SUFFIXES CL)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(openclpp DEFAULT_MSG cl_include_dir)

add_library(openclpp INTERFACE)
add_library(OpenCL::OpenCLPP ALIAS openclpp)

target_compile_definitions(openclpp INTERFACE
		CL_HPP_ENABLE_EXCEPTIONS
		CL_HPP_CL_1_2_DEFAULT_BUILD
		CL_HPP_TARGET_OPENCL_VERSION=120
		CL_HPP_MINIMUM_OPENCL_VERSION=120
		)

target_include_directories(openclpp INTERFACE ${cl_include_dir})