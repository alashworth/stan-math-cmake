# convenience method for constructing "plain" math unit tests
# emulates the current Stan math makefile
function(add_math_unit_test name)
	add_executable(${name} ${ARGN})
	set_target_properties(${name} PROPERTIES LINKER_LANGUAGE CXX)
	target_link_libraries(${name} PRIVATE Stan::Math GTest::GTest GTest::Main)
	target_include_directories(${name} PRIVATE
			$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/tests/math_unit>
			$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/tests/math_unit>)
	gtest_discover_tests(${name})
endfunction()

add_math_unit_test(stan_math_misc_unit_tests
		math_c11_test.cpp
		math_include_test.cpp
		multiple_translation_units1.cpp
		multiple_translation_units2.cpp
		multiple_translation_units_test.cpp
		util.hpp)

if (TARGET Stan::MathOpenCl)
	add_executable(stan_math_opencl_unit_tests
			math/opencl/device_functions/digamma_test.cpp
			math/opencl/device_functions/log1m_exp_test.cpp
			math/opencl/device_functions/log1p_exp_test.cpp
			math/opencl/kernel_generator/binary_operation_test.cpp
			math/opencl/kernel_generator/operation_test.cpp
			math/opencl/kernel_generator/reference_kernel.hpp
			math/opencl/kernel_generator/scalar_test.cpp
			math/opencl/kernel_generator/type_str_test.cpp
			math/opencl/prim/add_test.cpp
			math/opencl/prim/cholesky_decompose_test.cpp
			math/opencl/prim/divide_columns_test.cpp
			math/opencl/prim/mdivide_left_tri_low_test.cpp
			math/opencl/prim/mdivide_right_tri_low_test.cpp
			math/opencl/prim/multiply_test.cpp
			math/opencl/prim/rep_matrix_test.cpp
			math/opencl/prim/rep_row_vector_test.cpp
			math/opencl/prim/rep_vector_test.cpp
			math/opencl/prim/subtract_test.cpp
			math/opencl/prim/transpose_test.cpp
			math/opencl/rev/bernoulli_logit_glm_lpmf_test.cpp
			math/opencl/rev/categorical_logit_glm_lpmf_test.cpp
			math/opencl/rev/copy_test.cpp
			math/opencl/rev/matrix_cl_test.cpp
			math/opencl/rev/neg_binomial_2_log_glm_lpmf_test.cpp
			math/opencl/rev/normal_id_glm_lpdf_test.cpp
			math/opencl/rev/ordered_logistic_glm_lpmf_test.cpp
			math/opencl/rev/poisson_log_glm_lpmf_test.cpp
			math/opencl/rev/sub_block_test.cpp
			math/opencl/rev/triangular_transpose_test.cpp
			math/opencl/rev/zeros_test.cpp
			math/opencl/assign_event_test.cpp
			math/opencl/async_test.cpp
			math/opencl/check_opencl_test.cpp
			math/opencl/check_test.cpp
			math/opencl/check_vector_test.cpp
			math/opencl/cholesky_decompose_test.cpp
			math/opencl/copy_test.cpp
			math/opencl/copy_triangular_test.cpp
			math/opencl/diagonal_multiply_test.cpp
			math/opencl/identity_test.cpp
			math/opencl/is_matrix_cl_test.cpp
			math/opencl/kernel_cl_test.cpp
			math/opencl/matrix_cl_test.cpp
			math/opencl/matrix_cl_view_test.cpp
			math/opencl/multiply_transpose_test.cpp
			math/opencl/opencl_context_test.cpp
			math/opencl/require_generics_test.cpp
			math/opencl/sub_block_test.cpp
			math/opencl/tri_inverse_test.cpp
			math/opencl/triangular_transpose_test.cpp
			math/opencl/zeros_test.cpp
			)
	target_include_directories(stan_math_opencl_unit_tests PRIVATE
			$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
			$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}>)
	target_link_libraries(stan_math_opencl_unit_tests PRIVATE
			Stan::MathOpenCl
			GTest::GTest
			GTest::Main)
	#gtest_discover_tests(stan_math_opencl_unit_tests)
endif ()