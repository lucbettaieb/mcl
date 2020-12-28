/**
 * Author: Luc Bettaieb, 2020
 * BSD-Licensed
 */

#ifndef MCL_PARTICLES_H
#define MCL_PARTICLES_H

// C++ Standard Library
#include <array>
#include <chrono>

namespace mcl {

// Note: If you change this constant, some unit tests may fail as it has inherently influenced the outcome
//       that they are expecting.
static constexpr size_t N_PARTICLES = 500;

// TODO(lucbettaieb): Consider making this a virtual class and then implementing a PoseState w/ type trait checking
/// The state that we are trying to track
struct State {
  /**
   * @brief Constructor to construct a state with a YAML node
   * 
   * @param config  The YAML node from which to construct the state from
   */
  State(const YAML::Node& config) :
    x(config["x"].as<double>()),
    y(config["y"].as<double>()),
    theta(config["theta"].as<double>())
  {}

  /// Initialization constructor for the State
  State(double x,
        double y,
        double theta) : 
    x(x),
    y(y),
    theta(theta)
  {}

  State() = default;

  /// The x position of the position to be tracked
  double x;

  /// The y position of the position to be tracked
  double y;

  /// The heading of the position to be tracked
  double theta;
};

// TODO(lucbettaieb): This should probably also be more generic, like the derivative of the state.
struct Measurement {
  /// Initialization constructor for the measurement
  Measurement(double v,
              double w,
              const std::chrono::time_point& stamp) :
    v(v),
    w(w),
    stamp(stamp) {}

  Measurement() = default;

  /// The observed linear velocity of the tracked position
  double v;

  /// The observed angular velocity of the tracked position
  double w;

  /// The time stamp of the measurment
  std::chrono::time_point stamp;
};

struct Particle {
  Particle(const State& state, double weight) :
    state(state),
    weight(weight)
  {}

  Particle() = default;

  /// The hypothesized state of the system according to this particle
  State state;

  /// The weight of this particle
  double weight;
};

typedef std::array<Particle, N_PARTICLES> ParticleArray;

}  // namespace mcl
#endif  // MCL_PARTICLE_H
