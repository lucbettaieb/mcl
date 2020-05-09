/**
 * Author: Luc Bettaieb, 2020
 * BSD-Licensed
 */

#ifndef MCL_PARTICLE_FILTER_H
#define MCL_PARTICLE_FILTER_H

// MCL
#include "particle_filter_params.h"
#include "particles.h"

// MCL Stages
#include "stages/distributor.h"
#include "stages/extractor.h"
#include "stages/resampler.h"
#include "stages/scorer.h"
#include "stages/updater.h"

namespace mcl {

class ParticleFilter {
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

  /// The distributor to run in the particle filter
  const stages::Distributor::Ptr distributor;

  /// The updater to run in the particle filter
  const stages::Updater::Ptr updater;

  /// The scorer to run in the particle filter
  const stages::Scorer::Ptr scorer;

  /// The resampler to run in the particle filter
  const stages::Resampler::Ptr resampler;

  /// The extractor to run in the particle filter
  const stages::Extractor::Ptr extractor;

  /// The particles that the filter will operate on
  ParticleArray particles_;
};

}  // namespace mcl

#endif  // MCL_PARTICLE_FILTER_H
