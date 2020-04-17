/**
 * Author: Luc Bettaieb, 2020
 * BSD-Licensed
 */

#ifndef MCL_STAGES_UPDATER
#define MCL_STAGES_UPDATER

// C++ Standard Library
#include <memory>

// MCL
#include "../particles.h"

namespace mcl {
namespace stages {

class Updater {
 public:
  typedef std::shared_ptr<Updater> Ptr;

  explicit Updater();

  virtual ~Updater();

  virtual void update(ParticleArray::iterator begin, ParticleArray::iterator end) = 0;
};

}  // namespace stages

}  // namespace mcl

#endif  // MCL_STAGES_STATE_EXTRACTOR_H
