#include <stan/math/rev/arr.hpp>
#include <gtest/gtest.h>
#include <vector>

using stan::math::check_greater_or_equal;
using stan::math::var;

TEST(AgradRevErrorHandlingScalar, CheckFiniteVarCheckVectorized) {
  using stan::math::check_greater_or_equal;
  using stan::math::var;
  using std::vector;

  int N = 5;
  const char* function = "check_greater_or_equal";
  vector<var> a;

  for (int i = 0; i < N; ++i)
    a.push_back(var(i));

  size_t stack_size = stan::math::chainable_stack.var_stack_.size();

  EXPECT_EQ(5U, stack_size);
  EXPECT_NO_THROW(check_greater_or_equal(function, "a", a, -1.0));

  size_t stack_size_after_call
      = stan::math::chainable_stack.var_stack_.size();
  EXPECT_EQ(5U, stack_size_after_call);

  EXPECT_THROW(check_greater_or_equal(function, "a", a, 2.0),
               std::domain_error);
  stack_size_after_call
      = stan::math::chainable_stack.var_stack_.size();
  EXPECT_EQ(5U, stack_size_after_call);

  stan::math::recover_memory();
}
