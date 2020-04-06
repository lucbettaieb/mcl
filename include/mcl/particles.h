/**
 * Author: Luc Bettaieb, 2020
 * BSD-Licensed
 */

#ifndef MCL_PARTICLES_H
#define MCL_PARTICLES_H

// C++ Standard Library
#include <array>

namespace mcl
{

static constexpr size_t N_PARTICLES = 500;

/// The state that we are trying to track
struct State
{
	double x;
	double y;
};

struct Particle
{
	/// The hypothesized state of the system according to this particle
	State state;

	/// The weight of this particle
	double weight;
};

typedef std::array<Particle, N_PARTICLES> ParticleArray;

}  // namespace mcl
#endif  // MCL_PARTICLE_H
