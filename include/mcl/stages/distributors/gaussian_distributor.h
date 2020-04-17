/**
 * Author: Luc Bettaieb, 2020
 * BSD-Licensed
 */

#ifndef MCL_STAGES_DISTRIBUTORS_GAUSSIAN_DISTRIBUTOR_H
#define MCL_STAGES_DISTRIBUTORS_GAUSSIAN_DISTRIBUTOR_H

// C++ Standard Library
#include <memory>

// MCL
#include "../particles.h"

namespace mcl {
namespace stages {
namespace distributors {

class GaussianDistributor : public Distributor {
 public:
  typedef Distributor super;

  explicit GaussianDistributor() = default;

  virtual ~GaussianDistributor();

  void distribute(ParticleArray::iterator begin, ParticleArray::iterator end);
};

}  // namespace distributors
}  // namespace stages
}  // namespace mcl

#endif  // MCL_DISTRIBUTOR_H
