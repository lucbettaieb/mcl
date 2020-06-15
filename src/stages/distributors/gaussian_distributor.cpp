/**
 * Author: Luc Bettaieb, 2020
 * BSD-Licensed
 */

// C++ Standard Library
#include <random>

// MCL
#include "mcl/stages/distributors/gaussian_distributor.h"

namespace mcl {
namespace stages {
namespace distributors {

GaussianDistributor::GaussianDistributor(const GaussianDistributorParams& params) :
    params_(params),
    generator_(initializeGenerator(params.seed)) {
}

void GaussianDistributor::distribute(const mcl::State& initial_state,
                                     ParticleArray::iterator begin,
                                     ParticleArray::iterator end) {
  // This will distribute particles about an initial state according in a gaussian distribution
  std::normal_distribution<double> x_distribution{initial_state.x, params_.stddev.x};
  std::normal_distribution<double> y_distribution{initial_state.y, params_.stddev.y};
  std::normal_distribution<double> theta_distribution{initial_state.theta, params_.stddev.theta};

  // Iterate over all particles and assign their state to
  for (ParticleArray::iterator it = begin; it != end; ++it) {
    it->weight = 1.0;

    // TODO(luc): make state more generic
    it->state.x = x_distribution(generator_);
    it->state.y = y_distribution(generator_);
    it->state.theta = theta_distribution(generator_);
  }
}

}  // namespace distributors
}  // namespace stages
}  // namespace mcl
