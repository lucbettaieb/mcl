/**
 * Author: Luc Bettaieb, 2020
 * BSD-Licensed
 */

// GTest
#include <gtest/gtest.h>

// using namespace mcl;

TEST(ParticleFilterParamsTest, TestTest)
{
  std::cout << "?" << std::endl;
  ASSERT_TRUE(true);
}

int main(int argc, char **argv)
{
  std::cout << "??" << std::endl;
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
