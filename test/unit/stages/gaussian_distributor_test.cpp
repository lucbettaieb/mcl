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
