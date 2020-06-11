/**
 * Author: Luc Bettaieb, 2020
 * BSD-Licensed
 */

// GTest
#include <gtest/gtest.h>

// MCL
#include "mcl/stages/extractors/unimodal_extractor.h"

TEST(UnimodalExtractorTest, ConstructorTest)
{
  const YAML::Node test_config = YAML::LoadFile("test/config/extractors.yaml");
  mcl::stages::extractors::UnimodalExtractorParams p{test_config};

  mcl::stages::extractors::UnimodalExtractor dist{p};
  ASSERT_TRUE(true);
}
