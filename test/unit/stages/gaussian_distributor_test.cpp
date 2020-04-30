/**
 * Author: Luc Bettaieb, 2020
 * BSD-Licensed
 */

// GTest
#include <gtest/gtest.h>

// MCL
#include "mcl/stages/distributors/gaussian_distributor.h"

// using namespace mcl;

TEST(GaussianDistributorTest, TestTest)
{
  std::cout << "?" << std::endl;
  ASSERT_TRUE(true);
}

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
