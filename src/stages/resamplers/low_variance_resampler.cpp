/**
 * Author: Luc Bettaieb, 2020
 * BSD-Licensed
 */

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
  const float factor = 1.0 / mcl::N_PARTICLES;

  std::uniform_real_distribution<float> distribution(range_from, range_to)

  const float r = factor * rngUniform(0, 1);
  float c = p_[0].w;
  float u;

  //! Do resamplig
  for (uint32_t m = 0, i = 0; m < p_.size(); ++m)
  {
    u = r + factor * m;
    while (u > c)
    {
      if (++i >= p_.size())
        break;
      c += p_[i].w;
    }
    new_p[m] = p_[i];
    new_p[m].w = factor;
  }

}  // namespace resamplers
}  // namespace stages
}  // namespace mcl
