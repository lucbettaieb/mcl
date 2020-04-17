/**
 * Author: Luc Bettaieb, 2020
 * BSD-Licensed
 */

#ifndef MCL_STAGES_EXTRACTOR
#define MCL_STAGES_EXTRACTOR

// C++ Standard Library
#include <memory>

// MCL
#include "../particles.h"

namespace mcl {
namespace stages {

class Extractor {
 public:
  typedef std::shared_ptr<Extractor> Ptr;

  explicit Extractor();

  virtual ~Extractor();

  virtual void extractState(ParticleArray::iterator begin, ParticleArray::iterator end) = 0;
};
}  // namespace stages
}  // namespace mcl

#endif  // MCL_STAGES_EXTRACTOR_H
