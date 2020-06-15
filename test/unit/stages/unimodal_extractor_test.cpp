/**
 * Author: Luc Bettaieb, 2020
 * BSD-Licensed
 */

// GTest
#include <gtest/gtest.h>

// MCL
#include "mcl/stages/distributors/gaussian_distributor.h"
#include "mcl/stages/extractors/unimodal_extractor.h"


TEST(UnimodalExtractorTest, ConstructorTest) {
  const YAML::Node test_config = YAML::LoadFile("test/config/extractors.yaml");
  mcl::stages::extractors::UnimodalExtractorParams p{test_config};

  mcl::stages::extractors::UnimodalExtractor ext{p};
  ASSERT_TRUE(true);
}

TEST(UnimodalExtractorTest, ExtractTestBaseline) {
  const YAML::Node test_config = YAML::LoadFile("test/config/extractors.yaml");
  mcl::stages::extractors::UnimodalExtractorParams p{test_config};

  mcl::stages::extractors::UnimodalExtractor ext{p};
  mcl::stages::distributors::GaussianDistributor dist{{YAML::LoadFile("test/config/distributors.yaml")}};

  mcl::ParticleArray particles{};

  const double recovery_error = 0.05;

  for (const mcl::Particle& p : particles) {
    ASSERT_TRUE(p.state.x == 0.0 and p.state.y == 0.0 and p.state.theta == 0.0 and p.weight == 0.0);
  }

  mcl::State mean{0.0, 0.0, 0.0};
  dist.distribute(mean, particles.begin(), particles.end());

  mcl::State extracted_mean{-1.0, -1.0, -1.0};
  ext.extract(particles.begin(), particles.end(), &extracted_mean);

  ASSERT_TRUE(std::fabs(extracted_mean.x - mean.x) <= recovery_error);
  ASSERT_TRUE(std::fabs(extracted_mean.y - mean.y) <= recovery_error);
  ASSERT_TRUE(std::fabs(extracted_mean.theta - mean.theta) <= recovery_error);
}

TEST(UnimodalExtractorTest, ExtractTest) {
  const YAML::Node test_config = YAML::LoadFile("test/config/extractors.yaml");
  mcl::stages::extractors::UnimodalExtractorParams p{test_config};

  mcl::stages::extractors::UnimodalExtractor ext{p};
  mcl::stages::distributors::GaussianDistributor dist{{YAML::LoadFile("test/config/distributors.yaml")}};

  mcl::ParticleArray particles{};

  const double recovery_error = 0.05;

  for (const mcl::Particle& p : particles) {
    ASSERT_TRUE(p.state.x == 0.0 and p.state.y == 0.0 and p.state.theta == 0.0 and p.weight == 0.0);
  }

  for (double x = 0.0; x < 3.0; x += 0.25) {
    for (double y = 0.0; y < 3.0; y += 0.25) {
      for (double theta = 0.0; theta < 2 * M_PI; theta += 0.5) {
        mcl::State mean{x, y, theta};
        dist.distribute(mean, particles.begin(), particles.end());

        mcl::State extracted_mean{-1.0, -1.0, -1.0};
        ext.extract(particles.begin(), particles.end(), &extracted_mean);

        ASSERT_TRUE(std::fabs(extracted_mean.x - mean.x) <= recovery_error);
        ASSERT_TRUE(std::fabs(extracted_mean.y - mean.y) <= recovery_error);
        ASSERT_TRUE(std::fabs(extracted_mean.theta - mean.theta) <= recovery_error);
      }
    }
  }
}
