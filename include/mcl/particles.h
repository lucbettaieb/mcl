/**
 * Author: Luc Bettaieb, 2020
 * BSD-Licensed
 */

#ifndef MCL_PARTICLES_H
#define MCL_PARTICLES_H

// C++ Standard Library
#include <array>

namespace mcl {

static constexpr size_t N_PARTICLES = 500;

/// The state that we are trying to track
struct State  // TODO(lucbettaieb): Consider making this a virtual class and then implementing a PoseState w/ type trait
              // checking
{
  /// The x position of the position to be tracked
  double x;

  /// The y position of the position to be tracked
  double y;

  /// The heading of the position to be tracked
  double theta;
};

struct Particle {
  /// The hypothesized state of the system according to this particle
  State state;

  /// The weight of this particle
  double weight;
};

typedef std::array<Particle, N_PARTICLES> ParticleArray;

}  // namespace mcl
#endif  // MCL_PARTICLE_H
