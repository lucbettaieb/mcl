/**
 * Author: Luc Bettaieb, 2020
 * BSD-Licensed
 */

#ifndef MCL_STAGES_SCORER
#define MCL_STAGES_SCORER

// C++ Standard Library
#include <memory>

// MCL
#include "mcl/particles.h"

// YAML
#include <yaml-cpp/yaml.h>

namespace mcl {
namespace stages {

class Scorer {
 public:
  typedef std::shared_ptr<Scorer> Ptr;

  explicit Scorer();

  virtual ~Scorer();

  virtual void score(ParticleArray::iterator begin, ParticleArray::iterator end) = 0;
};
}  // namespace stages

}  // namespace mcl

#endif  // MCL_STAGES_STATE_EXTRACTOR_H
