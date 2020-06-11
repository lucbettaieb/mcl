/**
 * Author: Luc Bettaieb, 2020
 * BSD-Licensed
 */

// GTest
#include <gtest/gtest.h>

// MCL
#include "mcl/particle_filter_params.h"

TEST(ParticleFilterParamsTest, ConstructorTest)
{
  const YAML::Node test_config = YAML::LoadFile("test/config/particle_filter.yaml");
  mcl::ParticleFilterParams params(test_config);
  ASSERT_TRUE(true);
}
