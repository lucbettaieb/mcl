/**
 * Author: Luc Bettaieb, 2020
 * BSD-Licensed
 */

#ifndef MCL_PARTICLE_FILTER_H
#define MCL_PARTICLE_FILTER_H

// MCL
#include "particle_filter_params.h"
#include "particles.h"

namespace mcl
{

class ParticleFilter
{
public:
  /**
   * @brief Constructor for the particle filter
   * 
   * @param params  Parameters for the particle filter
   */
  explicit ParticleFilter(const ParticleFilterParams& params);

  /// A function to execute the particle filter
  void execute();

private:
  /// Parameters for the particle filter
  const ParticleFilterParams params_;

  // const Distributor distributor;

  // const Updater updater;

  // const Scorer scorer;

  // const Resampler resampler;

  // const PoseExtractor pose_extractor;

  /// The particles that the filter will operate on
  ParticleArray particles_;
};

} // namespace mcl

#endif  // MCL_PARTICLE_FILTER_H
