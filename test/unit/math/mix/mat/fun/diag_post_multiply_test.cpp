#include <test/unit/math/test_ad.hpp>

void expect_diag_post_multiply(const Eigen::MatrixXd& a,
                               const Eigen::VectorXd& v,
                               const stan::test::ad_tolerances& tols) {
  auto f = [](const auto& x, const auto& y) {
    return stan::math::diag_post_multiply(x, y);
  };
  stan::test::expect_ad(tols, f, a, v);
  Eigen::RowVectorXd rv(v);
  stan::test::expect_ad(tols, f, a, rv);
}
void expect_diag_post_multiply(const Eigen::MatrixXd& a,
                               const Eigen::VectorXd& v) {
  stan::test::ad_tolerances tols;
  expect_diag_post_multiply(a, v, tols);
}

TEST(MathMixMatFun, diagPostMultiply) {
  // 0 x 0
  Eigen::MatrixXd a00(0, 0);
  Eigen::VectorXd u0(0);
  expect_diag_post_multiply(a00, u0);

  // 1 x 1
  Eigen::MatrixXd a11(1, 1);
  a11 << 10;
  Eigen::VectorXd u1(1);
  u1 << 3;
  expect_diag_post_multiply(a11, u1);

  // 2 x 2
  Eigen::MatrixXd a22(2, 2);
  a22 << 1, 10, 100, 1000;
  Eigen::VectorXd u2(2);
  u2 << 2, 3;
  expect_diag_post_multiply(a22, u2);

  // 3 x 3
  Eigen::MatrixXd a33b(3, 3);
  a33b << 1, 2, 3, 2, 3, 4, 4, 5, 6;
  Eigen::VectorXd u3b(3);
  u3b << 1, 2, 3;
  expect_diag_post_multiply(a33b, u3b);

  Eigen::MatrixXd a33c(3, 3);
  a33c << 1, 2, 3, 4, 5, 6, 7, 8, 9;
  Eigen::VectorXd u3c(3);
  u3c << 1, 2, 3;
  expect_diag_post_multiply(a33c, u3c);

  stan::test::ad_tolerances tols;
  tols.hessian_hessian_ = 2e-2;       // default 1e-3
  tols.hessian_fvar_hessian_ = 2e-2;  // default 1e-3

  Eigen::MatrixXd a33(3, 3);
  a33 << 1, 10, 100, 1000, 2, -4, 8, -16, 32;
  Eigen::VectorXd u3(3);
  u3 << -1.7, 111.2, -29.3;
  expect_diag_post_multiply(a33, u3, tols);

  Eigen::MatrixXd a33d(3, 3);
  a33d << 1, 0, 0, 0, 2, 0, 0, 0, 3;
  Eigen::VectorXd u3d(3);
  u3d << 1, 2, 3;
  expect_diag_post_multiply(a33d, u3d, tols);

  // error: mismatched sizes
  expect_diag_post_multiply(a33, u2);
  expect_diag_post_multiply(a22, u3);

  // error: non-square
  Eigen::MatrixXd b23(2, 3);
  b23 << 1, 2, 3, 4, 5, 6;
  expect_diag_post_multiply(b23, u2);
}
