/**
 * Author: Luc Bettaieb, 2020
 * BSD-Licensed
 */

// GTest
#include <gtest/gtest.h>

// MCL
#include "mcl/stages/distributors/gaussian_distributor.h"

// using namespace mcl;

TEST(GaussianDistributorTest, ConstructorTest)
{
  const YAML::Node test_config = YAML::LoadFile("test/unit/stages/distributors.yaml");
  mcl::stages::distributors::GaussianDistributorParams p{test_config};

  mcl::stages::distributors::GaussianDistributor dist{p};
  ASSERT_TRUE(true);
}

TEST(GaussianDistributorTest, DistributeTest)
{
  const YAML::Node test_config = YAML::LoadFile("test/unit/stages/distributors.yaml");
  mcl::stages::distributors::GaussianDistributorParams params{test_config};

  mcl::stages::distributors::GaussianDistributor dist{params};

  mcl::ParticleArray particles{};

  for (const mcl::Particle& p : particles) {
    ASSERT_TRUE(p.state.x == 0.0 and p.state.y == 0.0 and p.state.theta == 0.0 and p.weight == 0.0);
  }

  mcl::State mean{0.0, 0.0, 0.0};
  dist.distribute(mean, particles.begin(), particles.end());

  double sum_err_x = 0.0;
  double sum_err_y = 0.0;
  double sum_err_theta = 0.0;

  for (const mcl::Particle& p : particles) {
    sum_err_x += (p.state.x - mean.x)*(p.state.x - mean.x);
    sum_err_y += (p.state.y - mean.y)*(p.state.y - mean.y);
    sum_err_theta += (p.state.theta - mean.theta)*(p.state.theta - mean.theta);
  }

  const double recovered_stddev_x = std::sqrt((1.0 / static_cast<double>(particles.size()-1)) * sum_err_x);
  const double recovered_stddev_y = std::sqrt((1.0 / static_cast<double>(particles.size()-1)) * sum_err_y);
  const double recovered_stddev_theta = std::sqrt((1.0 / static_cast<double>(particles.size()-1)) * sum_err_theta);

  const double recovery_error = 0.05;

  ASSERT_TRUE(std::fabs(recovered_stddev_x - params.stddev.x) <= recovery_error);
  ASSERT_TRUE(std::fabs(recovered_stddev_y - params.stddev.y) <= recovery_error);
  ASSERT_TRUE(std::fabs(recovered_stddev_theta - params.stddev.theta) <= recovery_error);
}
