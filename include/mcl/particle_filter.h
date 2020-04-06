/**
 * Author: Luc Bettaieb, 2020
 * BSD-Licensed
 */

#ifndef MCL_PARTICLE_FILTER_H
#define MCL_PARTICLE_FILTER_H

namespace mcl
{

// MCL
#include "mcl/particle_filter_params.h"

class ParticleFilter
{
public:
  /**
   * @brief Constructor for the particle filter
   * 
   * @param params  Parameters for the particle filter
   */
  explicit ParticleFilter(const ParticleFilterParams& params);

private:
  /// Parameters for the particle filter
  ParticleFilterParams params_;
};

} // namespace mcl

#endif  // MCL_PARTICLE_FILTER_H
