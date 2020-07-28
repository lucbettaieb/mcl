/**
 * Author: Luc Bettaieb, 2020
 * BSD-Licensed
 */

// GTest
#include <gtest/gtest.h>

// MCL
#include "mcl/stages/distributors/gaussian_distributor.h"
#include "mcl/stages/resamplers/low_variance_resampler.h"

TEST(LowVarianceResamplerTest, ConstructorTest) {
  const YAML::Node test_config = YAML::LoadFile("test/config/resamplers.yaml");
  mcl::stages::resamplers::LowVarianceResamplerParams p{test_config};

  mcl::stages::resamplers::LowVarianceResampler resampler{p};
  ASSERT_TRUE(true);
}

TEST(LowVarianceResamplerTest, ResampleZeroTest) {
  const YAML::Node test_config = YAML::LoadFile("test/config/resamplers.yaml");
  mcl::stages::resamplers::LowVarianceResamplerParams p{test_config};

  mcl::stages::resamplers::LowVarianceResampler resampler{p};

  mcl::ParticleArray particles{};

  for (const mcl::Particle& p : particles) {
    ASSERT_TRUE(p.state.x == 0.0 and p.state.y == 0.0 and p.state.theta == 0.0 and p.weight == 0.0);
  }

  resampler.resample(particles.begin(), particles.end());

   for (const mcl::Particle& p : particles) {
    ASSERT_TRUE(p.state.x == 0.0 and p.state.y == 0.0 and p.state.theta == 0.0 and p.weight == 0.0);
  }
}

TEST(LowVarianceResamplerTest, ResampleNonZeroMeanZeroWeightTest) {
  const YAML::Node test_config = YAML::LoadFile("test/config/resamplers.yaml");
  mcl::stages::resamplers::LowVarianceResamplerParams p{test_config};

  mcl::stages::resamplers::LowVarianceResampler resampler{p};

  mcl::ParticleArray particles{};

  const YAML::Node distributor_config = YAML::LoadFile("test/config/distributors.yaml");
  mcl::stages::distributors::GaussianDistributorParams params{distributor_config};

  mcl::stages::distributors::GaussianDistributor dist{params};

  mcl::State mean{1.0, 2.0, 0.707};
  dist.distribute(mean, particles.begin(), particles.end());

  resampler.resample(particles.begin(), particles.end());

  double sum_err_x = 0.0;
  double sum_err_y = 0.0;
  double sum_err_theta = 0.0;

  for (const mcl::Particle& p : particles) {
    sum_err_x += (p.state.x - mean.x) * (p.state.x - mean.x);
    sum_err_y += (p.state.y - mean.y) * (p.state.y - mean.y);
    sum_err_theta += (p.state.theta - mean.theta) * (p.state.theta - mean.theta);
  }

  const double recovered_stddev_x = std::sqrt((1.0 / static_cast<double>(particles.size() - 1)) * sum_err_x);
  const double recovered_stddev_y = std::sqrt((1.0 / static_cast<double>(particles.size() - 1)) * sum_err_y);
  const double recovered_stddev_theta = std::sqrt((1.0 / static_cast<double>(particles.size() - 1)) * sum_err_theta);

  const double recovery_error = 0.05;

  ASSERT_TRUE(std::fabs(recovered_stddev_x - params.stddev.x) <= recovery_error);
  ASSERT_TRUE(std::fabs(recovered_stddev_y - params.stddev.y) <= recovery_error);
  ASSERT_TRUE(std::fabs(recovered_stddev_theta - params.stddev.theta) <= recovery_error);
}

TEST(LowVarianceResamplerTest, ResampleTest) {
  const YAML::Node test_config = YAML::LoadFile("test/config/resamplers.yaml");
  mcl::stages::resamplers::LowVarianceResamplerParams p{test_config};

  mcl::stages::resamplers::LowVarianceResampler resampler{p};

  mcl::ParticleArray particles{};

  const YAML::Node distributor_config = YAML::LoadFile("test/config/distributors.yaml");
  mcl::stages::distributors::GaussianDistributorParams params{distributor_config};

  mcl::stages::distributors::GaussianDistributor dist{params};

  const size_t half_particlearray_size = static_cast<size_t>(mcl::N_PARTICLES / 2.0);

  mcl::State mean{1.0, 2.0, 0.707};
  dist.distribute(mean, particles.begin(), particles.end() - half_particlearray_size);

  mean = mcl::State{1.7, 2.2, 0.504};
  dist.distribute(mean, particles.begin() + half_particlearray_size, particles.end());


  for (double i = 0; i < static_cast<double>(mcl::N_PARTICLES); i++) {
    if (i < half_particlearray_size) {
      particles.at(i).weight = 0.73;
    } else {
      particles.at(i).weight = 0.25;
    }
  }

  size_t i = 0;
  for (auto p : particles) {
    if (i < 5) {
      std::cout << "[x: " << p.state.x << ", y: " << p.state.y  << ", th: " << p.state.theta << ", w: " << p.weight << "] ";
    }
    i++;
  }
  std::cout << std::endl;
  std::cout << std::endl;

  resampler.resample(particles.begin(), particles.end());

  i = 0;
  for (auto p : particles) {
    if (i < 5) {
      std::cout << "[x: " << p.state.x << ", y: " << p.state.y  << ", th: " << p.state.theta << ", w: " << p.weight << "] ";
    }
    i++;
  }
  std::cout << std::endl;

  // double sum_err_x = 0.0;
  // double sum_err_y = 0.0;
  // double sum_err_theta = 0.0;

  // for (const mcl::Particle& p : particles) {
  //   sum_err_x += (p.state.x - mean.x) * (p.state.x - mean.x);
  //   sum_err_y += (p.state.y - mean.y) * (p.state.y - mean.y);
  //   sum_err_theta += (p.state.theta - mean.theta) * (p.state.theta - mean.theta);
  // }

  // const double recovered_stddev_x = std::sqrt((1.0 / static_cast<double>(particles.size() - 1)) * sum_err_x);
  // const double recovered_stddev_y = std::sqrt((1.0 / static_cast<double>(particles.size() - 1)) * sum_err_y);
  // const double recovered_stddev_theta = std::sqrt((1.0 / static_cast<double>(particles.size() - 1)) * sum_err_theta);

  // const double recovery_error = 0.05;

  // ASSERT_TRUE(std::fabs(recovered_stddev_x - params.stddev.x) <= recovery_error);
  // ASSERT_TRUE(std::fabs(recovered_stddev_y - params.stddev.y) <= recovery_error);
  // ASSERT_TRUE(std::fabs(recovered_stddev_theta - params.stddev.theta) <= recovery_error);
}


