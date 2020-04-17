/**
 * Author: Luc Bettaieb, 2020
 * BSD-Licensed
 */

#ifndef MCL_STAGES_RESAMPLER
#define MCL_STAGES_RESAMPLER

// C++ Standard Library
#include <memory>

// MCL
#include "../particles.h"

namespace mcl {
namespace stages {

class Resampler {
 public:
  typedef std::shared_ptr<Resampler> Ptr;

  explicit Resampler();

  virtual ~Resampler();

  virtual void resample(ParticleArray::iterator begin, ParticleArray::iterator end) = 0;
};
}  // namespace stages
}  // namespace mcl

#endif  // MCL_STAGES_STATE_EXTRACTOR_H
