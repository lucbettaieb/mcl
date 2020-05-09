/**
 * Author: Luc Bettaieb, 2020
 * BSD-Licensed
 */

#ifndef MCL_STAGES_DISTRIBUTORS_GAUSSIAN_DISTRIBUTOR_H
#define MCL_STAGES_DISTRIBUTORS_GAUSSIAN_DISTRIBUTOR_H

// C++ Standard Library
#include <chrono>
#include <random>
#include <memory>

// YAML
#include <yaml-cpp/yaml.h>

// MCL
#include "mcl/particles.h"
#include "mcl/stages/distributor.h"

namespace mcl {
namespace stages {
namespace distributors {

struct GaussianDistributorParams : DistributorParams {
  /**
   * @brief Constructor for the GaussianDistributorParams
   * 
   * @param config  The YAML Node from which to load the configuration
   */
  GaussianDistributorParams(const YAML::Node& config) :
    DistributorParams(config),
    seed(config["gaussian_distributor"]["seed"].as<int>())
  {}

  /// A seed for the random number generator (-1 --> time)
  int32_t seed;
};

class GaussianDistributor : public Distributor {
 public:
  /**
   * @brief Constructor for the GaussianDistributor
   * 
   * @param params  A parameter struct for the GaussianDistributor
   */
  explicit GaussianDistributor(const GaussianDistributorParams& params);

  /// Destruction for the GaussianDistributor
  ~GaussianDistributor() = default;

  /**
   * @brief Distributes the particles about an initial_state in a normal distribution
   * 
   * @param initial_state  The initial state to function as the mean of the normal distribution
   * @param begin  The beginning of the particle array
   * @param end  The end of the particle array
   */
  void distribute(const mcl::State& initial_state, ParticleArray::iterator begin, ParticleArray::iterator end);

 private:
  /// A helper function to initialize the mt19937 PRNG
  std::mt19937 initializeGenerator(int32_t seed) {
    if (seed == -1) {
      return std::mt19937(std::chrono::system_clock::now().time_since_epoch().count());
    } else {
      return std::mt19937(seed);
    }
  }

  /// Parameters for the gaussian distributor
  GaussianDistributorParams params_;

  /// A mersenne-prime twister probabilistic random number generator
  std::mt19937 generator_;
};

}  // namespace distributors
}  // namespace stages
}  // namespace mcl

#endif  // MCL_DISTRIBUTOR_H
