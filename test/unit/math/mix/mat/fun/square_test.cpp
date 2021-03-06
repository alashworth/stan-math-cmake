#include <test/unit/math/test_ad.hpp>

TEST(mathMixMatFun, square) {
  auto f = [](const auto& x1) { return stan::math::square(x1); };
  stan::test::expect_common_unary_vectorized(f);
  stan::test::expect_unary_vectorized(f, -2.6, -1.0, -0.5, -0.2, 0.5, 1.3, 3, 5,
                                      1e5);
}
