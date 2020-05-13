/**
 * Author: Luc Bettaieb, 2020
 * BSD-Licensed
 */

#ifndef MCL_STAGES_EXTRACTOR
#define MCL_STAGES_EXTRACTOR

// C++ Standard Library
#include <memory>

// YAML
#include <yaml-cpp/yaml.h>

// MCL
#include "mcl/particles.h"

namespace mcl {
namespace stages {

/// Base parameter struct for the extractor
struct ExtractorParams {
  /**
   * @brief Constructor for the ExtractorParams
   * 
   * @param config  A YAML config node from which to load parameters
   */
  ExtractorParams(const YAML::Node& config)
  {}

  /// Destructor for the ExtractorParams
  virtual ~ExtractorParams() = default;
};

class Extractor {
 public:
  /// Convenience typedef for a shared pointer to the class
  typedef std::shared_ptr<Extractor> Ptr;

  /// Destructor for the extractor
  virtual ~Extractor() = default;

  /// Function prototype for the extractor
  virtual void extract(ParticleArray::iterator begin,
                       ParticleArray::iterator end,
                       mcl::State* extracted_state) = 0;
};
}  // namespace stages
}  // namespace mcl

#endif  // MCL_STAGES_EXTRACTOR_H
