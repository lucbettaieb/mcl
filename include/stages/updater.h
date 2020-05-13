/**
 * Author: Luc Bettaieb, 2020
 * BSD-Licensed
 */

#ifndef MCL_STAGES_UPDATER
#define MCL_STAGES_UPDATER

// C++ Standard Library
#include <memory>

// YAML
#include <yaml-cpp/yaml.h>

// MCL
#include "mcl/particles.h"

namespace mcl {
namespace stages {

/// Base parameter struct for the updater
struct UpdaterParams {
  /**
   * @brief Constructor for the UpdaterParams
   * 
   * @param config  A YAML config node from which to load parameters
   */
  UpdaterParams(const YAML::Node& config)
  {}

  /// Destructor for the UpdaterParams
  virtual ~UpdaterParams() = default;
};

class Updater {
 public:
  /// Convenience typedef for a shared pointer to the class
  typedef std::shared_ptr<Updater> Ptr;

  /// Destructor for the updater
  virtual ~Updater() = default;

  /// Function prototype for the updater
  virtual void update(ParticleArray::iterator begin, ParticleArray::iterator end) = 0;
};

}  // namespace stages

}  // namespace mcl

#endif  // MCL_STAGES_STATE_EXTRACTOR_H
