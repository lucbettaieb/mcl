/**
 * Author: Luc Bettaieb, 2020
 * BSD-Licensed
 */

#ifndef MCL_STAGES_DISTRIBUTOR_H
#define MCL_STAGES_DISTRIBUTOR_H

// C++ Standard Library
#include <memory>

// MCL
#include "../particles.h"

namespace mcl {
namespace stages {

class Distributor {
 public:
  typedef std::shared_ptr<Distributor> Ptr;

  explicit Distributor() = default;

  virtual ~Distributor();

  virtual void distribute(ParticleArray::iterator begin, ParticleArray::iterator end);
};
}  // namespace stages
}  // namespace mcl

#endif  // MCL_DISTRIBUTOR_H
