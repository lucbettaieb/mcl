/**
 * Author: Luc Bettaieb, 2020
 * BSD-Licensed
 */

#ifndef MCL_STAGES_DISTRIBUTOR_H
#define MCL_STAGES_DISTRIBUTOR_H

// C++ Standard Library
#include <memory>

// MCL
#include "../particles.h"

namespace mcl {
namespace stages {

/// Base parameter struct for the distributor
struct DistributorParams {
  /**
   * @brief Constructor for the DistributorParams
   * 
   * @param config  A YAML config node from which to load parameters
   */
  DistributorParams(const YAML::Node& config) :
    stddev(config["distributor"]["standard_deviation"])
  {}

  /// Destructor for the DistributorParams
  virtual ~DistributorParams();

  /// The standard deviations for all elements in the state
  State stddev;
};

class Distributor {
 public:
  typedef std::shared_ptr<Distributor> Ptr;

  // delete me?
  explicit Distributor() = default;

  virtual ~Distributor();

  virtual void distribute(ParticleArray::iterator begin, ParticleArray::iterator end) = 0;
};
}  // namespace stages
}  // namespace mcl

#endif  // MCL_DISTRIBUTOR_H
