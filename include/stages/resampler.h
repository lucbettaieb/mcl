/**
 * Author: Luc Bettaieb, 2020
 * BSD-Licensed
 */

#ifndef MCL_STAGES_RESAMPLER
#define MCL_STAGES_RESAMPLER

// C++ Standard Library
#include <memory>

// YAML
#include <yaml-cpp/yaml.h>

// MCL
#include "mcl/particles.h"

namespace mcl {
namespace stages {

/// Base parameter struct for the resampler
struct ResamplerParams {
  /**
   * @brief Constructor for the ResamplerParams
   * 
   * @param config  A YAML config node from which to load parameters
   */
  ResamplerParams(const YAML::Node& config)
  {}

  /// Destructor for the ResamplerParams
  virtual ~ResamplerParams() = default;
};

class Resampler {
 public:
  /// Convenience typedef for a shared pointer to the class
  typedef std::shared_ptr<Resampler> Ptr;

  virtual ~Resampler() = default;

  /// Function prototype for the resampler
  virtual void resample(ParticleArray::iterator begin, ParticleArray::iterator end) = 0;
};
}  // namespace stages
}  // namespace mcl

#endif  // MCL_STAGES_STATE_EXTRACTOR_H
