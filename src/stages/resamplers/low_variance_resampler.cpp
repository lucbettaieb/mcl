/**
 * Author: Luc Bettaieb, 2020
 * BSD-Licensed
 */

// C++ Standard Library
#include <random>
#include <iostream>
// MCL
#include "mcl/stages/resamplers/low_variance_resampler.h"

namespace mcl {
namespace stages {
namespace resamplers {

LowVarianceResampler::LowVarianceResampler(const LowVarianceResamplerParams& params) :
    params_(params) {
}

void LowVarianceResampler::resample(ParticleArray::iterator begin,
                                    ParticleArray::iterator end) {
  const double factor = 1.0 / mcl::N_PARTICLES;

  std::uniform_real_distribution<double> distribution(0, factor);
  std::mt19937 gen(params_.seed);
  const double r = distribution(gen);

  double c = begin->weight;
  size_t i = 0;

  ParticleArray resampled_particles{};
  ParticleArray::iterator iter = begin;

  for (size_t m = 1; m <= mcl::N_PARTICLES; m++) {
    const double u = r + (m - 1) * factor;
    while (u > c and i < mcl::N_PARTICLES) {
      i++;
      c += iter->weight;
    }
    resampled_particles[m-1] = (*iter);

    iter++;
  }

  i = 0;
  for (iter = begin; iter != end; iter++) {
    *iter = resampled_particles[i];
    i++;
  }
}

}  // namespace resamplers
}  // namespace stages
}  // namespace mcl
