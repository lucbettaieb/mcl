/**
 * Author: Luc Bettaieb, 2020
 * BSD-Licensed
 */

// GTest
#include <gtest/gtest.h>

// MCL
#include "mcl/stages/distributors/gaussian_distributor.h"
#include "mcl/stages/resamplers/low_variance_resampler.h"
#include "mcl/stages/extractors/unimodal_extractor.h"

TEST(LowVarianceResamplerTest, ConstructorTest) {
  const YAML::Node test_config = YAML::LoadFile("test/config/resamplers.yaml");
  mcl::stages::resamplers::LowVarianceResamplerParams p{test_config};

  mcl::stages::resamplers::LowVarianceResampler resampler{p};
  ASSERT_TRUE(true);
}

TEST(LowVarianceResamplerTest, ResampleZeroTest) {
  const double recovery_error = 0.00001;

  const YAML::Node test_config = YAML::LoadFile("test/config/resamplers.yaml");
  mcl::stages::resamplers::LowVarianceResamplerParams p{test_config};

  mcl::stages::resamplers::LowVarianceResampler resampler{p};

  mcl::ParticleArray particles{};

  for (const mcl::Particle& p : particles) {
    ASSERT_TRUE(p.state.x == 0.0 and p.state.y == 0.0 and p.state.theta == 0.0 and p.weight == 0.0);
  }

  resampler.resample(particles.begin(), particles.end());

   for (const mcl::Particle& p : particles) {
    ASSERT_NEAR(p.state.x, 0.0, recovery_error);
    ASSERT_NEAR(p.state.y, 0.0, recovery_error);
    ASSERT_NEAR(p.state.theta, 0.0, recovery_error);
    ASSERT_NEAR(p.weight, 0.0, recovery_error);
  }
}

TEST(LowVarianceResamplerTest, ResampleNonZeroMeanZeroWeightTest) {
  const YAML::Node test_config = YAML::LoadFile("test/config/resamplers.yaml");
  mcl::stages::resamplers::LowVarianceResamplerParams p{test_config};

  mcl::stages::resamplers::LowVarianceResampler resampler{p};

  mcl::ParticleArray particles{};

  const YAML::Node config_yaml = YAML::LoadFile("test/config/distributors.yaml");
  mcl::stages::distributors::GaussianDistributorParams gd_params{config_yaml};
  mcl::stages::distributors::GaussianDistributor dist{gd_params};

  mcl::stages::extractors::UnimodalExtractorParams ue_params{config_yaml};
  mcl::stages::extractors::UnimodalExtractor extractor{ue_params};

  mcl::State mean{1.0, 2.0, 0.707};
  dist.distribute(mean, particles.begin(), particles.end());

  resampler.resample(particles.begin(), particles.end());

  mcl::State extracted_state{};
  extractor.extract(particles.begin(), particles.end(), &extracted_state);

  double sum_err_x = 0.0;
  double sum_err_y = 0.0;
  double sum_err_theta = 0.0;

  for (const mcl::Particle& p : particles) {
    sum_err_x += (p.state.x - extracted_state.x) * (p.state.x - extracted_state.x);
    sum_err_y += (p.state.y - extracted_state.y) * (p.state.y - extracted_state.y);
    sum_err_theta += (p.state.theta - extracted_state.theta) * (p.state.theta - extracted_state.theta);
  }

  const double recovered_stddev_x = std::sqrt((1.0 / static_cast<double>(particles.size() - 1)) * sum_err_x);
  const double recovered_stddev_y = std::sqrt((1.0 / static_cast<double>(particles.size() - 1)) * sum_err_y);
  const double recovered_stddev_theta = std::sqrt((1.0 / static_cast<double>(particles.size() - 1)) * sum_err_theta);

  // TODO(lucbettaieb): Make this test a bit more rigorous.
  const double recovery_error = 0.05;

  ASSERT_TRUE((recovered_stddev_x - gd_params.stddev.x) <= recovery_error);
  ASSERT_TRUE((recovered_stddev_y - gd_params.stddev.y) <= recovery_error);
  ASSERT_TRUE((recovered_stddev_theta - gd_params.stddev.theta) <= recovery_error);
}

TEST(LowVarianceResamplerTest, ResampleTest) {
  const YAML::Node resampler_config = YAML::LoadFile("test/config/resamplers.yaml");
  mcl::stages::resamplers::LowVarianceResamplerParams lvr_params{resampler_config};
  mcl::stages::resamplers::LowVarianceResampler resampler{lvr_params};

  const YAML::Node distributor_config = YAML::LoadFile("test/config/distributors.yaml");
  mcl::stages::distributors::GaussianDistributorParams gd_params{distributor_config};
  mcl::stages::distributors::GaussianDistributor dist{gd_params};

  const YAML::Node extractor_config = YAML::LoadFile("test/config/extractors.yaml");
  mcl::stages::extractors::UnimodalExtractorParams ue_params{extractor_config};
  mcl::stages::extractors::UnimodalExtractor extractor{ue_params};

  mcl::ParticleArray particles{};

  const size_t half_particlearray_size = static_cast<size_t>(mcl::N_PARTICLES / 2.0);

  mcl::State mean{1.0, 2.0, 0.707};
  dist.distribute(mean, particles.begin(), particles.end() - half_particlearray_size);

  mean = mcl::State{1.7, 2.2, 0.504};
  dist.distribute(mean, particles.begin() + half_particlearray_size, particles.end());

  for (double i = 0; i < static_cast<double>(mcl::N_PARTICLES); i++) {
    if (i < half_particlearray_size) {
      particles.at(i).weight = 0.20;
    } else {
      particles.at(i).weight = 0.44;
    }
  }

  resampler.resample(particles.begin(), particles.end());

  mcl::State extracted_state{};
  extractor.extract(particles.begin(), particles.end(), &extracted_state);

  double sum_err_x = 0.0;
  double sum_err_y = 0.0;
  double sum_err_theta = 0.0;

  for (const mcl::Particle& p : particles) {
    sum_err_x += (p.state.x - extracted_state.x) * (p.state.x - extracted_state.x);
    sum_err_y += (p.state.y - extracted_state.y) * (p.state.y - extracted_state.y);
    sum_err_theta += (p.state.theta - extracted_state.theta) * (p.state.theta - extracted_state.theta);
  }

  const double recovered_stddev_x = std::sqrt((1.0 / static_cast<double>(particles.size() - 1)) * sum_err_x);
  const double recovered_stddev_y = std::sqrt((1.0 / static_cast<double>(particles.size() - 1)) * sum_err_y);
  const double recovered_stddev_theta = std::sqrt((1.0 / static_cast<double>(particles.size() - 1)) * sum_err_theta);

  // TODO(lucbettaieb): Make this test a bit more rigorous.
  const double recovery_error = 0.05;

  ASSERT_TRUE((recovered_stddev_x - gd_params.stddev.x) <= recovery_error);
  ASSERT_TRUE((recovered_stddev_y - gd_params.stddev.y) <= recovery_error);
  ASSERT_TRUE((recovered_stddev_theta - gd_params.stddev.theta) <= recovery_error);

}
