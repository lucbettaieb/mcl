/**
 * Author: Luc Bettaieb, 2020
 * BSD-Licensed
 */

#ifndef MCL_STAGES_UPDATERS_DIFF_DRIVE_UPDATER_H
#define MCL_STAGES_UPDATERS_DIFF_DRIVE_UPDATER_H

#include "mcl/stages/updater.h"

namespace mcl {
namespace stages {
namespace updaters {

struct DiffDriveUpdaterParams : public UpdaterParams {
  /**
   * @brief Constructor for the DiffDriveUpdaterParams
   *
   * @param config  The YAML Node from which to load the configuration
   */
  DiffDriveUpdaterParams(const YAML::Node& config) :
      UpdaterParams(config),
      seed(config["diff_drive_updater"]["seed"].as<int>()),
      alpha_1(config["diff_drive_updater"]["alpha_1"].as<double>()),
      alpha_2(config["diff_drive_updater"]["alpha_2"].as<double>()),
      alpha_3(config["diff_drive_updater"]["alpha_3"].as<double>()),
      alpha_4(config["diff_drive_updater"]["alpha_4"].as<double>()),
      alpha_5(config["diff_drive_updater"]["alpha_5"].as<double>()),
      alpha_6(config["diff_drive_updater"]["alpha_6"].as<double>()) {
  }

  /// A seed for the random number generator used when adding noise to the motion model
  int32_t seed;

  double alpha_1;
  double alpha_2;

  double alpha_3;
  double alpha_4;

  double alpha_5;
  double alpha_6;
};

class DiffDriveUpdater : public Updater {
 public:
  /**
   * @brief Constructor for the DiffDriveUpdater
   *
   * @param params  A parameter struct for the DiffDriveUpdater
   */
  explicit DiffDriveUpdater(const DiffDriveUpdaterParams& params);

  /// Destructor for the DiffDriveUpdater
  ~DiffDriveUpdater() = default;

  /**
   * @brief Updates the particles according to a differential drive motion model
   *
   * @param begin  The beginning of the particle array
   * @param end  The end of the particle array
   * @param measurment  The difference between the prior state and the new state according to the motion measurement
   */
  void update(ParticleArray::iterator begin, ParticleArray::iterator end, const mcl::Measurement& measurement);

 private:
  /// Parameters for the diff drive updater
  DiffDriveUpdaterParams params_;

  /// The previous measurment for the diff drive system
  std::chrono::time_point<std::chrono::system_clock> previous_stamp_;

};

}  // namespace updaters
}  // namespace stages
}  // namespace mcl

#endif  // MCL_STAGES_UPDATERS_DIFF_DRIVE_UPDATER_H
