/**
 * Author: Luc Bettaieb, 2020
 * BSD-Licensed
 */

#ifndef MCL_STAGES_SCORER
#define MCL_STAGES_SCORER

// C++ Standard Library
#include <memory>

// YAML
#include <yaml-cpp/yaml.h>

// MCL
#include "mcl/particles.h"

namespace mcl {
namespace stages {

/// Base parameter struct for the Scorer
struct ScorerParams {
  /**
   * @brief Constructor for the ScorerParams
   * 
   * @param config  A YAML config node from which to load parameters
   */
  ScorerParams(const YAML::Node& config)
  {}

  /// Destructor for the ScorerParams
  virtual ~ScorerParams() = default;
};

class Scorer {
 public:
  /// Convenience typedef for a shared pointer to the class
  typedef std::shared_ptr<Scorer> Ptr;

  /// Destructor for the scorer
  virtual ~Scorer();

  /// Function prototype for the scorer
  virtual void score(ParticleArray::iterator begin, ParticleArray::iterator end) = 0;
};
}  // namespace stages

}  // namespace mcl

#endif  // MCL_STAGES_STATE_EXTRACTOR_H
